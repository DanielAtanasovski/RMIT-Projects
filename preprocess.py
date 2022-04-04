# Copyright 2022 Daniel Atanasovski
# Note: Header row is removed at end of preprocessing
from csv import QUOTE_ALL
import pandas as pd

print("Beginning Pre-Processing...")

# Columns to keep
keep_columns = ['rdf-schema#label', 'birthDate',
                'birthPlace_label', 'deathDate', 'field_label',
                'genre_label', 'instrument_label', 'nationality_label',
                'thumbnail', 'wikiPageID', 'description']

# Keep Columns we want when loading
csv = pd.read_csv("artist.csv", usecols=keep_columns)
# Keep null values as 'NULL'
csv.fillna("NULL", inplace=True)
# Export modifed csv
csv.to_csv("artist_processed.csv", index=False,
           header=True, quotechar='"', quoting=QUOTE_ALL)

print("Pre-Processing Done!")
