import os
from PIL import Image
import time

def convert_tga(input_file, output_file,x,y):
    # Open the TGA file
    with Image.open(input_file) as image:
        # Convert the image to RGBA format (32bpp)
        rgba_image = image.convert("RGBA")

        # Create a new image without color palette
        new_image = Image.new("RGBA", rgba_image.size)
        new_image.paste(rgba_image, mask=rgba_image.split()[3])

        resized_image = new_image.resize((x, y))

        # Save the resized image as uncompressed TGA
        resized_image.save(output_file, format="TGA", compress=0)

# Get the current directory
current_directory = os.getcwd()

# Iterate over each file in the directory
for filename in os.listdir(current_directory):
    # Check if the file is a .tga file
    if filename.endswith(".tga"):
        # Create the input and output file paths
        input_file = os.path.join(current_directory, filename)
        output_file = os.path.join(current_directory, filename)

        # Convert the TGA file
        convert_tga(input_file, output_file,10,7)#     41,26  82,52
