/*
 * Copyright (c) 2022. Daniel Atanasovski.
 */

import java.io.BufferedReader;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.time.LocalDate;
import java.time.format.DateTimeParseException;
import java.util.*;

public class CSVToRecordConverter {

    Map<String, Integer> fieldToIndex;

    long cleanTimeTaken      = 0L;
    long convertingTimeTaken = 0L;

    public CSVToRecordConverter() {
        // All field names
        fieldToIndex = new HashMap<>();
        fieldToIndex.put(RecordHeaderSchema.PersonName, -1);
        fieldToIndex.put(RecordHeaderSchema.BirthDate, -1);
        fieldToIndex.put(RecordHeaderSchema.BirthPlaceLabel, -1);
        fieldToIndex.put(RecordHeaderSchema.DeathDate, -1);
        fieldToIndex.put(RecordHeaderSchema.FieldLabel, -1);
        fieldToIndex.put(RecordHeaderSchema.GenreLabel, -1);
        fieldToIndex.put(RecordHeaderSchema.InstrumentLabel, -1);
        fieldToIndex.put(RecordHeaderSchema.NationalityLabel, -1);
        fieldToIndex.put(RecordHeaderSchema.Thumbnail, -1);
        fieldToIndex.put(RecordHeaderSchema.WikiPageID, -1);
        fieldToIndex.put(RecordHeaderSchema.Description, -1);
    }

    public long getCleanTimeTaken() {
        return cleanTimeTaken;
    }

    public long getConvertingTimeTaken() {
        return convertingTimeTaken;
    }

    /**
     * Given a CSV file, converts the provided data to a list of Record Objects
     *
     * @param fileName - filename of CSV file
     * @return - List of Record Objects
     */
    public List<Record> convert(String fileName) throws IOException {
        return convertToRecords(cleanData(readCSV(fileName)));
    }

    /**
     * Given a CSV file, converts the provided data to a heapFile
     *
     * @param fileName - filename of CSV file
     * @return - void
     */
    public void convertAndOutput(String fileName, int pageSize) throws IOException {
        convertToRecordsAndOutput(cleanData(readCSV(fileName)), pageSize);
    }

    /**
     * Converts CSV file to list of rows, seperated by tokens
     * Credit: https://www.baeldung.com/java-csv-file-array
     *
     * @param fileName - csv filename
     * @return - List of CSV Rows that are also lists seperated by tokens
     */
    private List<List<String>> readCSV(String fileName) throws IOException {
        List<List<String>> csvContents    = new ArrayList<>();
        FileReader         fileReader     = new FileReader(fileName);
        BufferedReader     bufferedReader = new BufferedReader(fileReader);

        System.out.println("1. Reading In File: " + fileName + "...");

        // Loop through file reading lines of the csv
        String currentLine;
        while ((currentLine = bufferedReader.readLine()) != null) {
            String[] contents = stripQuotes(currentLine.split(","));

            // Add list of tokens as an element of greater 'csvContents' list
            csvContents.add(Arrays.asList(contents));
        }
        return csvContents;
    }

    /**
     * Removes all quotes from all elements of content
     *
     * @param content string to remove quotes from
     * @return modified content
     */
    private String[] stripQuotes(String[] content) {
        for (int i = 0; i < content.length; i++) {
            content[i] = content[i].replaceAll("\"", "");
        }
        return content;
    }

    /**
     * Removes unused fields from list of rows of tokens
     *
     * @param csvContents - list of rows of tokens from CSV
     * @return - list of rows of tokens without unused fields
     */
    private List<List<String>> cleanData(List<List<String>> csvContents) throws IOException {
        long startTime = System.nanoTime();

        // We know row 0 is header
        // Rows 1,2,3 are useless and can be deleted
        // Rows 4-X are data and need to be pruned to only include the fields we need

        System.out.println("2. Cleaning Data...");

        // Ensure CSV file has all fieldnames
        if (!findAllHeaders(csvContents.get(0)))
            throw new IOException("Invalid CSV File!");

        // Remove useless rows
        csvContents.remove(3);
        csvContents.remove(2);
        csvContents.remove(1);
        // We have found header so no longer need it
        csvContents.remove(0);

        cleanTimeTaken = System.nanoTime() - startTime;
        return csvContents;
    }

    /**
     * Searches CSV contents first element in list for all headers and
     * populates 'fieldToIndex' to point to where field names are in row
     *
     * @return - Whether successful in finding all field headers
     */
    private boolean findAllHeaders(List<String> headerRow) {
        // Find field name locations
        for (int i = 0; i < headerRow.size(); i++) {
            String content = headerRow.get(i);
            if (fieldToIndex.containsKey(content)) {
                fieldToIndex.put(content, i);
            }
        }

        // Check if all are found
        return !fieldToIndex.containsValue(-1);
    }

    /**
     * Converts from list of rows of tokens without unused fields to Record objects
     *
     * @param cleanedCsvContents - list of rows of tokens without unused fields
     * @return - List of Record Objects
     */
    private List<Record> convertToRecords(List<List<String>> cleanedCsvContents) {
        List<Record> records = new ArrayList<>();


        String    personName;
        LocalDate birthDate;
        String    birthPlaceLabel;
        LocalDate deathDate;
        String    fieldLabel;
        String    genreLabel;
        String    instrumentLabel;
        String    nationalityLabel;
        String    thumbnail;
        int       wikiPageID;
        String    description;

        System.out.println("3. Converting Data to Records...");
        long startTime = System.nanoTime();
//        int    invalidBirthDates            = 0;
//        int    invalidDeathDates            = 0;
        int longestPersonNameBytes      = 0;
        int longestBirthPlaceLabelBytes = 0;
        int longestFieldLabelBytes      = 0;
        int longestGenreLabelBytes      = 0;
        int longestInstrumentLabelBytes = 0;
//        String longestGenre                 = "";
//        int    debugRow                     = 0;
        int longestNationalityLabelBytes = 0;
        int longestThumbnailBytes        = 0;
        int longestDescriptionBytes      = 0;


        for (List<String> cleanedCsvContent : cleanedCsvContents) {
            personName = cleanedCsvContent.get(fieldToIndex.get(RecordHeaderSchema.PersonName));
            if (personName.getBytes().length > longestPersonNameBytes)
                longestPersonNameBytes = personName.getBytes().length;

            // Handle Dates
            try {
                birthDate = LocalDate.parse(cleanedCsvContent.get(fieldToIndex.get(RecordHeaderSchema.BirthDate)));
            } catch (DateTimeParseException e) {
                birthDate = LocalDate.MAX;
//                invalidBirthDates++;
            }

            try {
                deathDate = LocalDate.parse(cleanedCsvContent.get(fieldToIndex.get(RecordHeaderSchema.DeathDate)));
            } catch (DateTimeParseException e) {
                deathDate = LocalDate.MAX;
//                invalidDeathDates++;
            }

            // Handle Integers
            try {
                wikiPageID = Integer.parseInt(cleanedCsvContent.get(fieldToIndex.get(RecordHeaderSchema.WikiPageID)));
            } catch (NumberFormatException e) {
                wikiPageID = Integer.MAX_VALUE;
            }


            birthPlaceLabel = cleanedCsvContent.get(fieldToIndex.get(RecordHeaderSchema.BirthPlaceLabel));

            if (birthPlaceLabel.getBytes().length > longestBirthPlaceLabelBytes)
                longestBirthPlaceLabelBytes = birthPlaceLabel.getBytes().length;

            fieldLabel = cleanedCsvContent.get(fieldToIndex.get(RecordHeaderSchema.FieldLabel));

            if (fieldLabel.getBytes().length > longestFieldLabelBytes)
                longestFieldLabelBytes = fieldLabel.getBytes().length;

            genreLabel = cleanedCsvContent.get(fieldToIndex.get(RecordHeaderSchema.GenreLabel));

            if (genreLabel.getBytes().length > longestGenreLabelBytes) {
                longestGenreLabelBytes = genreLabel.getBytes().length;
//                longestGenre = genreLabel;
//                debugRow = i;
            }


            instrumentLabel = cleanedCsvContent.get(fieldToIndex.get(RecordHeaderSchema.InstrumentLabel));

            if (instrumentLabel.getBytes().length > longestInstrumentLabelBytes) {
                longestInstrumentLabelBytes = instrumentLabel.getBytes().length;
            }


            nationalityLabel = cleanedCsvContent.get(fieldToIndex.get(RecordHeaderSchema.NationalityLabel));

            if (nationalityLabel.getBytes().length > longestNationalityLabelBytes)
                longestNationalityLabelBytes = nationalityLabel.getBytes().length;

            thumbnail = cleanedCsvContent.get(fieldToIndex.get(RecordHeaderSchema.Thumbnail));

            if (thumbnail.getBytes().length > longestThumbnailBytes)
                longestThumbnailBytes = thumbnail.getBytes().length;

            description = cleanedCsvContent.get(fieldToIndex.get(RecordHeaderSchema.Description));

            if (description.getBytes().length > longestDescriptionBytes)
                longestDescriptionBytes = description.getBytes().length;

            records.add(new Record(personName, birthDate, birthPlaceLabel,
                                   deathDate, fieldLabel, genreLabel, instrumentLabel,
                                   nationalityLabel, thumbnail, wikiPageID, description
            ));
        }
        convertingTimeTaken = System.nanoTime() - startTime;
        return records;
    }

    private void convertToRecordsAndOutput(List<List<String>> cleanedCsvContents, int pageSize) {
        System.out.println("Records Byte Size: " + Record.getMaxBytes());
        System.out.println("3. Converting Data to Records and Building Heap of pageSize " + pageSize + " ...");
        long startTime = System.nanoTime();

        // File
        // Output Records to HeapFile
        int recordsPerPage = Math.floorDiv(pageSize, Record.getMaxBytes());
        int pageCount      = 0;

        try (FileOutputStream fos = new FileOutputStream("heap." + pageSize)) {
            // Go through all records, at records per page increments
            for (int i = 0; i < cleanedCsvContents.size(); i += recordsPerPage) {
                pageCount++;
                // Align records after one another
                byte[] page = new byte[pageSize];
                for (int j = 0; j < recordsPerPage; j++) {
                    int index = i + j;

                    System.arraycopy(createRecord(cleanedCsvContents.get(index)).getBytes(), 0, page,
                                     j * Record.getMaxBytes(),
                                     Record.getMaxBytes());
                }
                // Write Page
                fos.write(page);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        System.out.println("HeapFile Page Count: " + pageCount);
        convertingTimeTaken = System.nanoTime() - startTime;
    }

    private Record createRecord(List<String> content) {
        String    personName;
        LocalDate birthDate;
        String    birthPlaceLabel;
        LocalDate deathDate;
        String    fieldLabel;
        String    genreLabel;
        String    instrumentLabel;
        String    nationalityLabel;
        String    thumbnail;
        int       wikiPageID;
        String    description;

        // Handle Dates
        try {
            birthDate = LocalDate.parse(content.get(fieldToIndex.get(RecordHeaderSchema.BirthDate)));
        } catch (DateTimeParseException e) {
            birthDate = LocalDate.MAX;
        }

        try {
            deathDate = LocalDate.parse(content.get(fieldToIndex.get(RecordHeaderSchema.DeathDate)));
        } catch (DateTimeParseException e) {
            deathDate = LocalDate.MAX;
        }

        // Handle Integers
        try {
            wikiPageID = Integer.parseInt(content.get(fieldToIndex.get(RecordHeaderSchema.WikiPageID)));
        } catch (NumberFormatException e) {
            wikiPageID = Integer.MAX_VALUE;
        }

        personName = content.get(fieldToIndex.get(RecordHeaderSchema.PersonName));
        birthPlaceLabel = content.get(fieldToIndex.get(RecordHeaderSchema.BirthPlaceLabel));
        fieldLabel = content.get(fieldToIndex.get(RecordHeaderSchema.FieldLabel));
        genreLabel = content.get(fieldToIndex.get(RecordHeaderSchema.GenreLabel));
        instrumentLabel = content.get(fieldToIndex.get(RecordHeaderSchema.InstrumentLabel));
        nationalityLabel = content.get(fieldToIndex.get(RecordHeaderSchema.NationalityLabel));
        thumbnail = content.get(fieldToIndex.get(RecordHeaderSchema.Thumbnail));
        description = content.get(fieldToIndex.get(RecordHeaderSchema.Description));

        return new Record(personName, birthDate, birthPlaceLabel,
                          deathDate, fieldLabel, genreLabel, instrumentLabel,
                          nationalityLabel, thumbnail, wikiPageID, description
        );
    }
}
