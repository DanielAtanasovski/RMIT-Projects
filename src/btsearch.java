import java.io.*;
import java.time.LocalDate;
import java.util.Arrays;

public class btsearch {
    public static void main(String[] args) {

        int    treePageSize       = 4096;
        int    recordLength   = Record.getMaxBytes();
        String nullTerminator = "\u0000";

        // Arguments validation
        if (args.length != 4) {
            System.out.println("Invalid Number of Arguments!");
            return;
        }

        // File Validation
        RandomAccessFile heapFile = null;
        try {
            heapFile = new RandomAccessFile(args[0], "r");
        } catch (FileNotFoundException e) {
            System.out.println("File Not Found!");
            return;
        }

        // File Validation
        FileInputStream indexFile = null;
        try {
            indexFile = new FileInputStream(args[1]);
        } catch (FileNotFoundException e) {
            System.out.println("File Not Found!");
            return;
        }

        // Get Pagesize
        String[] heapFileSplit = args[0].split("\\.");
        int heapPageSize = Integer.parseInt(heapFileSplit[1]);

        String[] indexFileSplit = args[1].split("\\.");
        int indexPageSize = Integer.parseInt(indexFileSplit[1]);

        // Date Argument Validation

        // From Date
        if (args[2].length() != 8) {
            System.out.println("Invalid From Date!");
            return;
        }

        int year, month, day;
        year = Integer.parseInt(args[2].substring(0, 4));
        month = Integer.parseInt(args[2].substring(4, 6));
        day = Integer.parseInt(args[2].substring(6, 8));
        LocalDate fromDate = LocalDate.of(year, month, day);

        // To Date
        if (args[3].length() != 8) {
            System.out.println("Invalid To Date!");
            return;
        }

        year = Integer.parseInt(args[3].substring(0, 4));
        month = Integer.parseInt(args[3].substring(4, 6));
        day = Integer.parseInt(args[3].substring(6, 8));
        LocalDate toDate = LocalDate.of(year, month, day);

        // Build Tree from object
        BPTree tree = null;
        try {
            ObjectInputStream ois = new ObjectInputStream(indexFile);
            tree = (BPTree) ois.readObject();
            ois.close();
        } catch (IOException e) {
            e.printStackTrace();
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }

        tree.printTree(false);


        // Read File
        byte[] pageBytes      = new byte[heapPageSize];
        int    bytesRead      = 0;
        int    records        = 0;
        int    recordsNotIncludingNull = 0;
        int    recordsMatched = 0;
        long   startTime      = System.nanoTime();

        // TODO: Create Tree from binary data

        long daysBetween = toDate.toEpochDay() - fromDate.toEpochDay();
        System.out.println("Searching Birthdates between: " + fromDate.toString() + " -> " + toDate.toString());
        System.out.println("Days between: " + daysBetween);
        System.out.println("-----------------------------");

        int recordsPerPage = (int) Math.floor(heapPageSize / Record.getMaxBytes());

        for (int i = 0; i < daysBetween; i++) {
            long value = tree.search(i);

            if (value == Long.MIN_VALUE)
                continue;


            // Pages to skip
            int pagesToSkip = (int) Math.floor(value / recordsPerPage);
            int recordsToSkip = (int) (value % recordsPerPage);

            int pageBytesToSkip = pagesToSkip * heapPageSize;
            int recordBytesToSkip = recordsToSkip * Record.getMaxBytes();

//            System.out.println( "records bytes to skip: " + recordBytesToSkip);

            try {
                heapFile.seek(pageBytesToSkip);
                int readBytes = heapFile.read(pageBytes);
//                System.out.println("Read: " + readBytes);

                byte[] recordBytes =
                        Arrays.copyOfRange(pageBytes, recordBytesToSkip,  recordBytesToSkip + Record.getMaxBytes());
                Record record = new Record(recordBytes);

                System.out.println("RecordID: " + value);
                System.out.println("Name: " + record.getPersonName());
                System.out.println("Date: " + record.getBirthDate());
            } catch (IOException e) {
                e.printStackTrace();
            }

        }

        long finalTime = System.nanoTime() - startTime;
        System.out.println("Query took " + ((double) finalTime / 1_000_000_000) + " Seconds.");
    }
}
