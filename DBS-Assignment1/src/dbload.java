/*
 * Copyright (c) 2022. Daniel Atanasovski.
 */

import java.io.IOException;

public class dbload {
    public static void main(String[] args) {
        CSVToRecordConverter csvToRecordConverter = new CSVToRecordConverter();

        int    pageSize = 4096;
        String fileName = "artist_processed.csv";

        // Process Commands
        if (args.length == 3) {
            // full args
            if (args[0].equalsIgnoreCase("-p")) {
                pageSize = Integer.parseInt(args[1]);
                fileName = args[2];
            } else {
                System.out.println("MALFORMED ARGUMENTS!");
                return;
            }
        } else if (args.length == 1) {
            // Provided datafile only
            fileName = args[0];
        } else {
            System.out.println("NO ARGUMENTS PROVIDED!");
            return;
        }

        // Determine if pageSize is too small
        if (pageSize < Record.getMaxBytes()) {
            System.out.println("PageSize is too small for fixed length records!");
            return;
        }

        // Convert CSV to Records
        try {
            csvToRecordConverter.convertAndOutput(fileName, pageSize);
        } catch (IOException e) {
            e.printStackTrace();
        }

        double cleanFileTimeTakenSeconds      = (double) csvToRecordConverter.getCleanTimeTaken() / 1_000_000_000;
        double convertingFileTimeTakenSeconds = (double) csvToRecordConverter.getConvertingTimeTaken() / 1_000_000_000;

        System.out.println("Time Taken to clean CSV file (seconds): " + cleanFileTimeTakenSeconds);
        System.out.println("Time Taken to convert CSV file to HeapFile (seconds): " + convertingFileTimeTakenSeconds);
    }
}
