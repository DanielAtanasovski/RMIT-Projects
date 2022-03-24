/*
 * Copyright (c) 2022. Daniel Atanasovski.
 */

import java.io.FileOutputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Timer;
import java.util.concurrent.TimeUnit;

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
        List<Record> records = new ArrayList<>();
        try {
            records = csvToRecordConverter.convert(fileName);
        } catch (IOException e) {
            e.printStackTrace();
        }

        System.out.println("Records Loaded: " + records.size());
        System.out.println("Records Byte Size: " + Record.getMaxBytes());
        System.out.println("5. Generating Heap File of page size " + pageSize + " bytes...");

        // Output Records to HeapFile
        int recordsPerPage = Math.floorDiv(pageSize, Record.getMaxBytes());
        int pageCount = 0;

        long startHeapFileTime = System.nanoTime();

        try (FileOutputStream fos = new FileOutputStream("heap." + pageSize)) {
            // Go through all records, at records per page increments
            for (int i = 0; i < records.size(); i += recordsPerPage) {
                pageCount++;
                // Align records after one another
                byte[] page = new byte[pageSize];
                for (int j = 0; j < recordsPerPage; j++) {
                    int index = i + j;
                    System.arraycopy(records.get(index).getBytes(), 0, page, j * Record.getMaxBytes(),
                                     Record.getMaxBytes());
                }
                // Write Page
                fos.write(page);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        long heapFileTimeTaken = System.nanoTime() - startHeapFileTime;
        double heapFileTimeTakenSeconds = (double) heapFileTimeTaken / 1_000_000_000;
        double cleanFileTimeTakenSeconds = (double) csvToRecordConverter.getCleanTimeTaken() / 1_000_000_000;
        double convertingFileTimeTakenSeconds = (double) csvToRecordConverter.getConvertingTimeTaken() / 1_000_000_000;


        System.out.println("HeapFile Page Count: " + pageCount);
        System.out.println("Time Taken to clean CSV file (seconds): " + cleanFileTimeTakenSeconds);
        System.out.println("Time Taken to convert CSV file to records (seconds): " + convertingFileTimeTakenSeconds);
        System.out.println("Time Taken to generate HeapFile (seconds): " + heapFileTimeTakenSeconds);
    }
}
