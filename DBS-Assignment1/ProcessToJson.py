import csv
import json

# Field names
fieldNames = ['personName']  # ETC...

# Open Processed CSV
with open('artist_processesd.csv', 'rb') as inputData:
    # Skip headers and useless rows
    next(inputData, None)
    next(inputData, None)
    next(inputData, None)
    next(inputData, None)

    # Create Reader
    reader = csv.DictReader(inputData, fie)
