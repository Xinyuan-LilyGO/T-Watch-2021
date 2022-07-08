#include "./TWatch_hal.h"

#if defined(CONFIG_TWATCH_HAS_BMA423)

#define GRAVITY_EARTH (9.80665f)

#if defined(TWATCH_AIO_INT)
#define BMA4_INT_MAP BMA4_INTR1_MAP
#else
#define BMA4_INT_MAP BMA4_INTR2_MAP
#endif

static float lsb_to_ms2(int16_t val, float g_range, uint8_t bit_width)
{
  float half_scale = (float)(1 << bit_width) / 2.0f;

  return GRAVITY_EARTH * val * g_range / half_scale;
}

int8_t readRegister(uint8_t reg, uint8_t *data, uint32_t len, void *intf_ptr)
{
  Wire.beginTransmission(BMA4_I2C_ADDR_PRIMARY);
  Wire.write(reg);
  Wire.endTransmission();
  Wire.requestFrom((uint8_t)BMA4_I2C_ADDR_PRIMARY, (uint8_t)len);
  uint8_t i = 0;
  while (Wire.available())
  {
    data[i++] = Wire.read();
  }
  return 0; // Pass
}

int8_t writeRegister(uint8_t reg, const uint8_t *data, uint32_t len, void *intf_ptr)
{
  Wire.beginTransmission(BMA4_I2C_ADDR_PRIMARY);
  Wire.write(reg);
  Wire.write(data, len);
  return (0 != Wire.endTransmission());
}

void delay_us(uint32_t period, void *intf_ptr)
{
  ets_delay_us(period);
}

int8_t bma4_interface_selection(struct bma4_dev *bma, uint8_t variant)
{
  int8_t rslt = BMA4_OK;
  uint8_t dev_addr;
  if (bma != NULL)
  {
    /* Select the interface for execution
     * For I2C : BMA4_I2C_INTF
     * For SPI : BMA4_SPI_INTF
     */
    bma->intf = BMA4_I2C_INTF;
    /* Bus configuration : I2C */
    if (bma->intf == BMA4_I2C_INTF)
    {
      printf("I2C Interface \n");

      /* To initialize the user I2C function */
      Wire.begin(TWATCH_IICSDA, TWATCH_IICSCL);
      dev_addr = BMA4_I2C_ADDR_PRIMARY;
      bma->bus_read = readRegister;
      bma->bus_write = writeRegister;
    }

    /* Assign variant parameter */
    bma->variant = BMA42X_VARIANT;
    /* Assign device address to interface pointer */
    bma->intf_ptr = &dev_addr;
    /* Configure delay in microseconds */
    bma->delay_us = delay_us;
    /* Configure max read/write length (in bytes) ( Supported length depends on target machine) */
    bma->read_write_len = 8;
  }
  else
  {
    rslt = BMA4_E_NULL_PTR;
  }

  return rslt;
}

void bma4_error_codes_print_result(const char api_name[], uint16_t rslt)
{
  if (rslt != BMA4_OK)
  {
    DEBUGF("%s\t", api_name);
    if (rslt & BMA4_E_NULL_PTR)
    {
      DEBUGF("Error [%d] : Null pointer\r\n", rslt);
    }
    else if (rslt & BMA4_E_CONFIG_STREAM_ERROR)
    {
      DEBUGF("Error [%d] : Invalid configuration stream\r\n", rslt);
    }
    else if (rslt & BMA4_E_SELF_TEST_FAIL)
    {
      DEBUGF("Error [%d] : Self test failed\r\n", rslt);
    }
    else if (rslt & BMA4_E_INVALID_SENSOR)
    {
      DEBUGF("Error [%d] : Device not found\r\n", rslt);
    }
    else
    {
      /* For more error codes refer "*_defs.h" */
      DEBUGF("Error [%d] : Unknown error code\r\n", rslt);
    }
  }
}

void TWatchClass::bma423_interface_init()
{
  bma423 = new bma4_dev;
  uint16_t rslt = bma4_interface_selection(bma423, BMA42X_VARIANT);
  bma4_error_codes_print_result("bma4_interface_selection status", rslt);
}

void TWatchClass::bma423_begin()
{
  uint16_t rslt;
  struct bma423_axes_remap remap;
  struct bma4_accel_config accel_conf;
  struct bma4_int_pin_config pin_config;
  bma423_reset();
  delay(50);

  rslt = bma423_init(bma423);
  bma4_error_codes_print_result("bma423_init", rslt);
  if (rslt == BMA4_OK)
    _isinited_bma423 = true;
  else
    DEBUGLN("bma423 not find");

  if (_isinited_bma423)
  {
    rslt = bma423_write_config_file(bma423);
    bma4_error_codes_print_result("bma423_write_config", rslt);

    remap.x_axis = 0;
    remap.x_axis_sign = 0;
    remap.y_axis = 1;
    remap.y_axis_sign = 1;
    remap.z_axis = 2;
    remap.z_axis_sign = 1;
    bma423_set_remap_axes(&remap, bma423);

    pin_config.edge_ctrl = BMA4_LEVEL_TRIGGER;
    pin_config.input_en = BMA4_INPUT_DISABLE;
    pin_config.lvl = BMA4_ACTIVE_LOW;
    pin_config.od = BMA4_PUSH_PULL;
    pin_config.output_en = BMA4_OUTPUT_ENABLE;
    bma4_set_int_pin_config(&pin_config, BMA4_INT_MAP, bma423);

    accel_conf.odr = BMA4_OUTPUT_DATA_RATE_100HZ;
    accel_conf.range = BMA4_ACCEL_RANGE_2G;
    accel_conf.bandwidth = BMA4_ACCEL_NORMAL_AVG4;
    accel_conf.perf_mode = BMA4_CIC_AVG_MODE;
    rslt = bma4_set_accel_config(&accel_conf, bma423);
    bma4_error_codes_print_result("bma4_set_accel_config status", rslt);

    bma423_acc_feature(true);
    // AccSensor_Feature(BMA423_WRIST_WEAR | BMA423_SINGLE_TAP | BMA423_DOUBLE_TAP | BMA423_STEP_CNTR, true);
    // AccSensor_Feature_Int(BMA423_WRIST_WEAR_INT | BMA423_STEP_CNTR_INT | BMA423_SINGLE_TAP_INT | BMA423_DOUBLE_TAP_INT, true);
    bma423_feature(BMA423_STEP_CNTR, true);
    bma423_feature_int(BMA423_STEP_CNTR_INT, false);

    /* Set water-mark level 1 to get interrupt after 20 steps.
     * Range of step counter interrupt is 0 to 20460(resolution of 20 steps).
     */
    rslt = bma423_step_counter_set_watermark(1, bma423);
    bma4_error_codes_print_result("bma423_step_counter status", rslt);
  }
}
/*
 *  @note Below macros are used to check the interrupt status.
 *
 * Feature Interrupts
/**\name Feature enable macros for the sensor
 * BMA423_STEP_CNTR
 * BMA423_WRIST_WEAR
 * BMA423_SINGLE_TAP
 * BMA423_DOUBLE_TAP
 */
void TWatchClass::bma423_feature(uint8_t feature, bool Enable)
{
  uint16_t rslt;
  if (_isinited_bma423)
  {
    rslt = bma423_feature_enable(feature, Enable, bma423);
    bma4_error_codes_print_result("bma423_feature_enable status", rslt);
  }
}
/*
 * Feature Interrupts
/**\name Interrupt status macros
*  BMA423_SINGLE_TAP_INT
*  BMA423_STEP_CNTR_INT
*  BMA423_WRIST_WEAR_INT
*  BMA423_DOUBLE_TAP_INT
*  BMA423_ACTIVITY_INT
*  BMA423_ANY_MOT_INT
*  BMA423_NO_MOT_INT
*  BMA423_ERROR_INT
 */
void TWatchClass::bma423_feature_int(uint8_t feature, bool Enable)
{
  uint16_t rslt;
  if (_isinited_bma423)
  {
    rslt = bma423_map_interrupt(BMA4_INT_MAP, feature, Enable, bma423);
    bma4_error_codes_print_result("bma423_map_interrupt status", rslt);
  }
}

void TWatchClass::bma423_updata(uint32_t millis, uint32_t time_ms)
{
  static uint32_t Millis;
  uint16_t int_status = 0;
  struct bma4_accel sens_data;
  if (millis - Millis > time_ms)
  {
    if (_isinited_bma423)
    {
      uint16_t rslt = bma423_read_int_status(&int_status, bma423);

      rslt = bma423_step_counter_output(&stepCount, bma423);

      rslt = bma4_read_accel_xyz(&sens_data, bma423);
      AccX = lsb_to_ms2(sens_data.x, 2, bma423->resolution);
      AccY = -lsb_to_ms2(sens_data.y, 2, bma423->resolution);
      AccZ = -lsb_to_ms2(sens_data.z, 2, bma423->resolution);
    }
    // DEBUGF("AccX:%.2f, AccY:%.2f, AccZ:%.2f\r\n", AccX, AccY, AccZ);
    Millis = millis;
  }
}

void TWatchClass::bma423_step_reset(void)
{
  if (_isinited_bma423)
  {
    bma423_reset_step_counter(bma423);
  }
}

void TWatchClass::bma423_acc_feature(bool Enable)
{
  if (_isinited_bma423)
  {
    uint16_t rslt = bma4_set_accel_enable(Enable, bma423);
    bma4_error_codes_print_result("bma4_set_accel_enable status", rslt);
  }
}
void TWatchClass::bma423_reset(void)
{
  bma4_soft_reset(bma423);
}

float TWatchClass::bma423_getX() { return AccX; }
float TWatchClass::bma423_getY() { return AccY; }
float TWatchClass::bma423_getZ() { return AccZ; }

uint32_t TWatchClass::bma423_get_step() { return stepCount; }

/*
 * @param[in] temp_unit : indicates the unit of temperature
 *
 * temp_unit   |   description
 * ------------|-------------------
 * BMA4_DEG    |   degrees Celsius
 * BMA4_FAHREN |   degrees fahrenheit
 * BMA4_KELVIN |   degrees kelvin
 *
 */
float TWatchClass::bma423_get_temperature(uint8_t temp_unit)
{
  int32_t get_temp = 0;
  float actual_temp = 0;
  if (_isinited_bma423)
  {
    bma4_get_temperature(&get_temp, temp_unit, bma423);
    actual_temp = (float)get_temp / (float)BMA4_SCALE_TEMP;
  }

  return actual_temp;
}
/*
 * Feature
 *  BMA423_SINGLE_TAP_INT
 *  BMA423_STEP_CNTR_INT
 *  BMA423_WRIST_WEAR_INT
 *  BMA423_DOUBLE_TAP_INT
 *  BMA423_ACTIVITY_INT
 *  BMA423_ANY_MOT_INT
 *  BMA423_NO_MOT_INT
 *  BMA423_ERROR_INT
 */
void TWatchClass::bma423_set_feature_event(uint8_t feature, irq_Fun_cb_t cb)
{
  switch (feature)
  {
  case BMA423_SINGLE_TAP_INT:
    _bma_irq_cb.single_tap_cb = cb;
    break;
  case BMA423_STEP_CNTR_INT:
    _bma_irq_cb.step_cntr_cb = cb;
    break;
  case BMA423_WRIST_WEAR_INT:
    _bma_irq_cb.wrist_wear_cb = cb;
    break;
  case BMA423_DOUBLE_TAP_INT:
    _bma_irq_cb.double_tap_cb = cb;
    break;
  case BMA423_ACTIVITY_INT:
    _bma_irq_cb.activity_cb = cb;
    break;
  case BMA423_ANY_MOT_INT:
    _bma_irq_cb.any_mot_cb = cb;
    break;
  case BMA423_NO_MOT_INT:
    _bma_irq_cb.no_mot_cb = cb;
    break;
  default:
    break;
  }
}

#endif