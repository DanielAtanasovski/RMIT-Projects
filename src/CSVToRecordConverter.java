/*
 * Copyright (c) 2022. Daniel Atanasovski.
 */

import java.io.*;
import java.util.*;

public class CSVToRecordConverter {

    Map<String, Integer> fieldToIndex;

    public CSVToRecordConverter(List<List<String>> csvContents) {
        // All field names
        fieldToIndex = new HashMap<String, Integer>();
        fieldToIndex.put("rdf-schema#label",    -1);
        fieldToIndex.put("birthDate",           -1);
        fieldToIndex.put("birthPlace_label",    -1);
        fieldToIndex.put("deathDate",           -1);
        fieldToIndex.put("field_label",         -1);
        fieldToIndex.put("genre_label",         -1);
        fieldToIndex.put("instrument_label",    -1);
        fieldToIndex.put("nationality_label",   -1);
        fieldToIndex.put("thumbnail",           -1);
        fieldToIndex.put("wikiPageID",          -1);
        fieldToIndex.put("description",         -1);
    }

    /**
     * Given a CSV file, converts the provided data to a list of Record Objects
     * @param fileName - filename of CSV file
     * @return - List of Record Objects
     */
    public List<Record> convert(String fileName) throws IOException {
        return convertToRecords(cleanData(readCSV(fileName)));
    }

    /**
     * Converts CSV file to list of rows, seperated by tokens
     * Credit: https://www.baeldung.com/java-csv-file-array
     * @param fileName - csv filename
     * @return - List of CSV Rows that are also lists seperated by tokens
     */
    private List<List<String>> readCSV(String fileName) throws IOException {
        List<List<String>> csvContents = new ArrayList<>();
        FileReader fileReader = new FileReader(fileName);
        BufferedReader bufferedReader = new BufferedReader(fileReader);

        // Loop through file reading lines of the csv
        String currentLine;
        while((currentLine = bufferedReader.readLine()) != null) {
            String[] contents = currentLine.split(",");
            // Add list of tokens as an element of greater 'csvContents' list
            csvContents.add(Arrays.asList(contents));
        }
        return csvContents;
    }

    /**
     * Removes unused fields from list of rows of tokens
     * @param csvContents - list of rows of tokens from CSV
     * @return - list of rows of tokens without unused fields
     */
    private List<List<String>> cleanData(List<List<String>> csvContents) throws IOException {
        // We know row 0 is header
        // Rows 1,2,3 are useless and can be deleted
        // Rows 4-X are data and need to be pruned to only include the fields we need

        // Ensure CSV file has all fieldnames
        if (!findAllHeaders(csvContents.get(0)))
            throw new IOException("Invalid CSV File!");

        // Remove useless rows
        csvContents.remove(3);
        csvContents.remove(2);
        csvContents.remove(1);
        // We have found header so no longer need it
        csvContents.remove(0);

        // Loop through all tokens and delete ones that are not necessary
//        for (int row = 0; row < csvContents.size(); row++) {
//            for (int token = csvContents.get(row).size(); token-- > 0; ) {
//                String content = csvContents.get(row).get(token);
//                if (!fieldToIndex.containsKey(content))
//                    csvContents.get(row).remove(token);
//            }
//        }

        return csvContents;
    }

    /**
     * Searches CSV contents first element in list for all headers and
     * populates 'fieldToIndex' to point to where field names are in row
     * @return - Whether successful in finding all field headers
     */
    private boolean findAllHeaders(List<String> headerRow) {
        // Find field name locations
        for (int i = 0; i < headerRow.size(); i++) {
            String content = headerRow.get(i);
            if (fieldToIndex.containsKey(content))
                fieldToIndex.put(content, i);
        }

        // Check if all are found
        if (!fieldToIndex.containsValue(-1))
            return true;

        return false;
    }

    /**
     * Converts from list of rows of tokens without unused fields to Record objects
     * @param cleanedCsvContents - list of rows of tokens without unused fields
     * @return - List of Record Objects
     */
    private List<Record> convertToRecords(List<List<String>> cleanedCsvContents) {
        List<Record> records = new ArrayList<>();

        String personName;
        Date birthDate;
        String birthPlaceLabel;
        Date deathDate;
        String fieldLabel;
        String genreLabel;
        String instrumentLabel;
        String nationalityLabel;
        String thumbnail;
        int wikiPageID;
        String description;

        for (int i = 0; i < cleanedCsvContents.size(); i++) {
            for (int j = 0; j < cleanedCsvContents.get(0).size(); j++) {

                personName = cleanedCsvContents.get(i).get(fieldToIndex.get("rdf-schema#label"));
                personName = cleanedCsvContents.get(i).get(fieldToIndex.get("rdf-schema#label"));
                personName = cleanedCsvContents.get(i).get(fieldToIndex.get("rdf-schema#label"));
                personName = cleanedCsvContents.get(i).get(fieldToIndex.get("rdf-schema#label"));
                personName = cleanedCsvContents.get(i).get(fieldToIndex.get("rdf-schema#label"));
                personName = cleanedCsvContents.get(i).get(fieldToIndex.get("rdf-schema#label"));
                personName = cleanedCsvContents.get(i).get(fieldToIndex.get("rdf-schema#label"));
                personName = cleanedCsvContents.get(i).get(fieldToIndex.get("rdf-schema#label"));


                records.add(new Record(
                        ,
                        cleanedCsvContents.get(i).get(fieldToIndex.get("rdf-schema#label")),
                        cleanedCsvContents.get(i).get(fieldToIndex.get("rdf-schema#label")),
                        cleanedCsvContents.get(i).get(fieldToIndex.get("rdf-schema#label")),
                        cleanedCsvContents.get(i).get(fieldToIndex.get("rdf-schema#label")),
                        cleanedCsvContents.get(i).get(fieldToIndex.get("rdf-schema#label")),

                ));

            }
        }

        return records;
    }
}
