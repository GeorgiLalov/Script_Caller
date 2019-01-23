'''
Created on Jun 9, 2017

@author: lalov
'''

#test

import os
import filecmp
from shutil import copyfile

waking_all_disks_command =  "fdisk -l"

mirrorFrom = ["/home/lalov/Pictures",
              "/home/lalov/Documents",
              "/home/lalov/Music"]
mirrorTo   = ["/run/media/lalov/Gogo's Disk/Lalov/Pics",
              "/run/media/lalov/Gogo's Disk/Lalov/Documents",
              "/run/media/lalov/Gogo's Disk/Lalov/Music"]

index = 0

def is_file_exist(fileName):
    return os.path.isfile(fileName)  

def is_dir_exist(directory):
    return os.path.isdir(directory)

def get_destination_file_full_path(root, fileName):
    base_path_lenght = len(mirrorFrom[index])
    
    return mirrorTo[index] + root[base_path_lenght:] + '/' + fileName

def get_source_file_full_path(root, fileName):
    return root + '/' + fileName

def get_destination_dir_full_path(root, ___dir):
    base_path_lenght = len(mirrorFrom[index])

    return mirrorTo[index] + root[base_path_lenght:] + '/' + ___dir

# True if they seem equal, False otherwise
def are_files_equal(file1, file2):
    return filecmp.cmp(file1, file2)

def recursive_walk(source_dir):
    for root, dirs, files in os.walk(source_dir):
        for ___dir in dirs:
            destination_dir = get_destination_dir_full_path(root, ___dir)
            
            if (is_dir_exist(destination_dir)):
                pass
            else:
                os.makedirs(destination_dir)

        for file in files:
            destination_path = get_destination_file_full_path(root, file)
            source_path      = get_source_file_full_path(root, file)
            
            if (is_file_exist(destination_path)):
                if (are_files_equal(source_path, destination_path)):
                    pass
                else:
                    copyfile(source_path, destination_path)
                    print ('coped from ' + source_path + ' to ' + destination_path)
            else:
                copyfile(source_path, destination_path)
                print ('coped from ' + source_path + ' to ' + destination_path)

if __name__ == '__main__':
    os.system(waking_all_disks_command)

    while (index < len(mirrorFrom)):
        recursive_walk(mirrorFrom[index])
        index += 1
           
    print ('Done')

