
"""
Myabe there is an easier way to construct a big indian word
but the python docs kind of suck...
"""
def read_word(f):
    word = f.read(4)
    val = (ord(word[0]) << 24) | (ord(word[1]) << 16) | (ord(word[2]) << 8) | (ord(word[3]) << 0)
    return val

def read_byte(f):
    return ord(f.read(1))

def render_val(val):
    ramp = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\|()1{}[]?-_+~<>i!lI;:,\"^`'. "
    return ramp[int((len(ramp)-1)*(1-val/255.0))]

with open("train-images.idx3-ubyte", "rb") as f:
    magic = read_word(f)
    num_images = read_word(f)
    pixel_width = read_word(f)
    pixel_height = read_word(f)

    print 'magic', magic
    print 'images', num_images
    print 'pixel_width', pixel_width
    print 'pixel_height', pixel_height

    for i in range(num_images):
        for y in range(pixel_height):
            line = ""
            for x in range(pixel_width):
                pixel = read_byte(f)
                line += render_val(pixel) * 1
            print line
