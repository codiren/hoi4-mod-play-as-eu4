from PIL import Image

def modify_image_colors(image_path, output_path):
    # Open the image
    image = Image.open(image_path)

    # Convert the image to RGB mode
    image = image.convert("RGB")

    # Get the width and height of the image
    width, height = image.size

    # Create a new image with the same size and mode
    new_image = Image.new("L", (width, height))

    # Define the color palette with the desired colors
    #palette = [0, 0, 0, 64, 64, 128]

    # Assign the color palette to the new image
    #new_image.putpalette(palette)

    # Iterate over each pixel in the image
    for y in range(height):
        for x in range(width):
            # Get the RGB values of the current pixel
            r, g, b = image.getpixel((x, y))

            # Check if the current color is not 32;32;64 or 64;64;128
            #if (r, g, b) != (64, 64, 128) and (r, g, b) != (32, 32, 64):
                # Replace the color with 64;64;128
                #new_image.putpixel((x, y), (56, 56, 114))
            #elif (r, g, b) == (64, 64, 128):
                #new_image.putpixel((x, y), (56, 56, 114))
            #else:
                # Keep the original color
            if r == 0:
                new_image.putpixel((x, y), 89)
            else:
                new_image.putpixel((x, y), r)

    # Save the modified image as an 8-bit depth BMP image
    new_image.save(output_path, "BMP")

# Provide the file paths for the input and output images
input_image_path = "terrain.bmp"
output_image_path = "terrain.bmp"

# Call the function to modify the image colors and save it
modify_image_colors(input_image_path, output_image_path)
