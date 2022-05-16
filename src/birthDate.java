/*
 * Copyright (c) 2022. Daniel Atanasovski.
 */

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.time.LocalDate;
import java.util.Arrays;

public class birthDate {

    public static void main(String[] args) {

        int    pageSize       = 4096;
        int    recordLength   = Record.getMaxBytes();
        String nullTerminator = "\u0000";


        // Arguments validation
        if (args.length != 3) {
            System.out.println("Invalid Arguments!");
            return;
        }

        // File Validation
        FileInputStream heapFile = null;
        try {
            heapFile = new FileInputStream(args[0]);
        } catch (FileNotFoundException e) {
            System.out.println("File Not Found!");
            return;
        }

        // Get Pagesize
        String[] heapFileSplit = args[0].split("\\.");
        pageSize = Integer.parseInt(heapFileSplit[1]);

        // Date Argument Validation

        // From Date
        if (args[1].length() != 8) {
            System.out.println("Invalid From Date!");
            return;
        }

        int year, month, day;
        year = Integer.parseInt(args[1].substring(0, 4));
        month = Integer.parseInt(args[1].substring(4, 6));
        day = Integer.parseInt(args[1].substring(6, 8));
        LocalDate fromDate = LocalDate.of(year, month, day);

        // To Date
        if (args[2].length() != 8) {
            System.out.println("Invalid To Date!");
            return;
        }

        year = Integer.parseInt(args[2].substring(0, 4));
        month = Integer.parseInt(args[2].substring(4, 6));
        day = Integer.parseInt(args[2].substring(6, 8));
        LocalDate toDate = LocalDate.of(year, month, day);

        // Read File
        byte[] pageBytes      = new byte[pageSize];
        int    bytesRead      = 0;
        int    records        = 0;
        int    recordsMatched = 0;
        long   startTime      = System.nanoTime();

        try {
            while ((bytesRead = heapFile.read(pageBytes)) != -1) {

                int recordBytesRead = 0;
                while ((recordBytesRead + Record.getMaxBytes()) <= pageSize) {
                    byte[]
                            recordBytes =
                            Arrays.copyOfRange(pageBytes, recordBytesRead, recordBytesRead + Record.getMaxBytes());
                    recordBytesRead += Record.getMaxBytes();
                    Record currentRecord = new Record(recordBytes);
                    if (currentRecord.getBirthDate().isAfter(fromDate) &&
                        currentRecord.getBirthDate().isBefore(toDate)) {
                        recordsMatched++;
//                        System.out.println("Result: " + currentRecord.getPersonName() + " | " +
//                                           currentRecord.getBirthDate().toString());
                    }
                    records += 1;
                }
            }

        } catch (IOException e) {
            System.out.println("Failed to read Heap File");
            return;
        }

        long finalTime = System.nanoTime() - startTime;
        System.out.println("Out of " + records + " records, only " + recordsMatched + " matched the query.");
        System.out.println("Query took " + ((double) finalTime / 1_000_000_000) + " Seconds.");
    }
}
