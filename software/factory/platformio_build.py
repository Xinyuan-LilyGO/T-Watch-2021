import os
import shutil

target_path = os.path.abspath('./lib/TWatch_2021_Library/')
source_path = os.path.abspath('../../TWatch_2021_Library/')

print(source_path)
print(target_path)

if not os.path.exists(target_path):
    shutil.copytree(source_path, target_path)
    print('copy dir finished!')
else:
    print('lib already exists!')
