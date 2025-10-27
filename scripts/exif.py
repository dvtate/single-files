from PIL import Image
import piexif
import random
import datetime
import os

IN_DIR="/home/tate/Pictures/footprintmaxxing-photos/input_imgs"
OUT_DIR="/home/tate/Pictures/footprintmaxxing-photos/output_imgs"

now = datetime.datetime.now().timestamp()

def add_exif_data(filename):
    # Load image
    img = Image.open(os.path.join(IN_DIR, filename))

    # Generate random EXIF data
    zeroth_ifd = {
        piexif.ImageIFD.Make: f"RandomMake{random.randint(1, 100)}",
        piexif.ImageIFD.Model: f"RandomModel{random.randint(1000, 9999)}",
        piexif.ImageIFD.Software: "RandomExifGenerator",
    }
    
    dt = datetime.datetime.fromtimestamp(now - random.randint(1, 1000000000))
    exif_ifd = {
        piexif.ExifIFD.DateTimeOriginal: dt.strftime("%Y:%m:%d %H:%M:%S"),
        piexif.ExifIFD.FNumber: (random.randint(1, 28) * 10, 10), # Example F-number
        piexif.ExifIFD.ExposureTime: (random.randint(1, 100), 1000), # Example Exposure Time
    }
    gps_ifd = {
        piexif.GPSIFD.GPSLatitudeRef: "N",
        piexif.GPSIFD.GPSLatitude: [(random.randint(0, 90), 1), (random.randint(0, 60), 1), (random.randint(0, 60), 1)],
        piexif.GPSIFD.GPSLongitudeRef: "W",
        piexif.GPSIFD.GPSLongitude: [(random.randint(0, 180), 1), (random.randint(0, 60), 1), (random.randint(0, 60), 1)],
    }

    exif_dict = {"0th": zeroth_ifd, "Exif": exif_ifd, "GPS": gps_ifd}
    exif_bytes = piexif.dump(exif_dict)

    # Save image with new EXIF data
    img.save(os.path.join(OUT_DIR, filename), exif=exif_bytes)
    
for filename in os.listdir(IN_DIR):
    add_exif_data(filename)
