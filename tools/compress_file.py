#!/usr/local/opt/python/libexec/bin/python

from PIL import Image
import sys
import random
import time

args = sys.argv
path_original = args[1]
path_compressed = args[2]

print(f'task for {path_original} was started')
time.sleep(randint(5,10))
print(f'task for {path_original} was finished')

image_original = Image.open(path_original)
image_size = image_original.size
new_size = (int(image_size[0]/2), int(image_size[1]/2))

#image_compressed = image_original.resize(new_size, Image.ANTIALIAS)
#image_compressed.save(path_compressed, optimize=True, quality=95)