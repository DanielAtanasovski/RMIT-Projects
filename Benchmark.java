import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class Benchmark {
    /** File path of file filled with processes */
    private static final String processFilePath = "processes.txt";
    /** Amount of times to test each implementation to get the average time */
    private static final int avgCount = 5;
    /** Value to divide nano time to convert to seconds */
    private static final double divisor = 1_000_000_000;

    /**
     * Main method.
     *
     * @param args The command line arguments.
     */
    public static void main(String[] args) {
        int amount = 10;
        String impl = "";
        String type = "";

        if (args.length <= 0)
            fail("Arguments: <Process Count> [Implementation {All}]");

        if (args.length < 2)
            amount = Integer.parseInt(args[0]);
        else if (args.length < 3) {
            amount = Integer.parseInt(args[0]);
            type = args[1].toLowerCase();
        } else {
            amount = Integer.parseInt(args[0]);
            type = args[1].toLowerCase();
            impl = args[2].toLowerCase();
        }

        // Error Checking
        if (type != "")
            if (!(type.equals("en")) && !(type.equals("de")) && !(type.equals("pt")))
                fail("Invalid Type");

        if (impl != "")
            if (!(impl.equals("a")) && !(impl.equals("l")) && !(impl.equals("b")) && !(impl.equals("array"))
                    && !(impl.equals("linkedlist")) && !(impl.equals("tree")))
                fail("Invalid Implementation");

        System.out.println("## Begin Benchmark ##");

        // List of processes
        List<String> processLines = getProcesses();
        System.out.println("Process Commands Count: " + processLines.size());

        List<Proc> processes = generateRandomProcesses(amount, processLines);
        run(impl, type, processes);

        System.out.println("## End Benchmark ##");
    }

    /**
     * Grabs the file of process labels and times and generates a list
     * 
     * @return String of Process labels and times
     */
    public static List<String> getProcesses() {
        List<String> processLines = new ArrayList<String>();
        try {
            BufferedReader reader = new BufferedReader(new FileReader(processFilePath));
            String line = reader.readLine();

            while (line != null) {
                processLines.add(line);
                line = reader.readLine();
            }

            reader.close();

        } catch (FileNotFoundException e) {
            fail(e.getMessage());
        } catch (IOException e) {
            fail(e.getMessage());
        }

        return processLines;
    }

    /**
     * Takes in a list of strings with labels and times, randomly selects and
     * generates a new node that is added into a list
     * 
     * @param amount Amount of random nodes desired
     * @param lines  List of strings to derive nodes from
     * @return list of Nodes
     */
    public static List<Proc> generateRandomProcesses(int amount, List<String> lines) {
        Random random = new Random();
        List<Proc> processes = new ArrayList<Proc>();

        for (int i = 0; i < amount; i++) {
            // Get a random index within list
            int index = random.nextInt(lines.size());
            // Split up the string into a label and time
            String[] sepProcess = lines.get(index).split(",");
            String label = sepProcess[0];
            int vtTime = Integer.parseInt(sepProcess[1]);
            // Create new Node and add it to the list
            Proc process = new Proc(label, vtTime);
            processes.add(process);
        }

        return processes;
    }

    /**
     * Begins the benchmark by determining what to test
     * 
     * @param impl      Implementation to test
     * @param type      Type to test
     * @param processes list of processes
     */
    public static void run(String impl, String type, List<Proc> processes) {
        if (impl.equals("") && type.equals("")) {
            // Testing all implementation & Types
            runAll(processes);
        } else if (impl.equals("")) {
            // Testing all implementations & 1 type
            runAllImpl(type, processes);
        } else {
            // Testing Specific
            Runqueue queue = null;
            switch (impl) {
                case "a":
                case "array":
                    queue = new OrderedArrayRQ();
                    break;
                case "l":
                case "linkedlist":
                    queue = new OrderedLinkedListRQ();
                    break;
                case "b":
                case "bst":
                    queue = new BinarySearchTreeRQ();
                    break;
                default:
                    fail("Invalid Implementation");
            }
            runImpl(queue, type, processes);
        }

    }

    /**
     * Tests a particular Implementation and type
     * 
     * @param impl  Implementation
     * @param times Times to test to determine average
     * @return void
     */
    public static void runImpl(Runqueue impl, String type, List<Proc> processes) {
        System.out.println("## Beginning " + type + " Test of " + impl.getClass().getName() + " ##");

        double[] averages = new double[avgCount];
        // Gonna Setup a filled queue for the dequeue and preceding tests
        // to save time enqueuing every loop for slow implementations.
        // (Looking at you OrderedArray)
        Runqueue filledImpl = null;
        try {
            filledImpl = impl.getClass().newInstance();
        } catch (InstantiationException | IllegalAccessException e) {
            fail(e.getMessage());
        }

        for (int i = 0; i < processes.size(); i++) {
            filledImpl.enqueue(processes.get(i).getLabel(), processes.get(i).getVt());
        }


        // Perform Test up to the amount needed for average
        for (int i = 0; i < avgCount; i++) {
            long time = 0;

            // Test
            switch (type){
                case "en":
                    time = runEn(impl, processes);
                    break;
                case "de":
                    time = runDe(filledImpl, processes);
                    break;
                case "pt":
                    time = runPt(filledImpl, processes);
                    break;
            }

            double seconds = (double) time / divisor;
            averages[i] = seconds;
            System.out.printf("Test: %d Time: %f seconds %n", i + 1, seconds);
        }

        // Calculate Total Average
        Double averageSum = 0d;
        for (int i = 0; i < averages.length; i++) {
            averageSum += averages[i];
        }
        Double average = averageSum / avgCount;
        System.out.println("## Completed " + type + " Test of " + impl.getClass().getName() + "With an avg time of " + average +" seconds ## \n");
    }

    /**
     * Performs the enqueue test
     * @param impl Implementation to perform test
     * @param processes list of processess
     * @return time taken
     */
    public static long runEn(Runqueue impl, List<Proc> processes) {
        long startTime = System.nanoTime();
        try {
            Runqueue newImpl = impl.getClass().newInstance();
            for (int i = 0; i < processes.size(); i++) {
                newImpl.enqueue(processes.get(i).getLabel(), processes.get(i).getVt());
            }
        } catch (InstantiationException e) {
            fail(e.getMessage());
        } catch (IllegalAccessException e) {
            fail(e.getMessage());
        }
        long endTime = System.nanoTime();
        return endTime - startTime;
    }

    /**
     * Performs the dequeue test
     * @param impl Implementation to perform test
     * @param processes list of processess
     * @return time taken
     */
    public static long runDe(Runqueue impl, List<Proc> processes) {
        // Test
        long startTime = System.nanoTime();
        for (int i = 0; i < processes.size(); i++) {
            impl.dequeue();
        }
        long endTime = System.nanoTime();
        return endTime - startTime;
    }

    /**
     * Performs the preceding time test
     * @param impl Implementation to perform test
     * @param processes list of processess
     * @return Time Taken
     */
    public static long runPt(Runqueue impl, List<Proc> processes) {
        // Not sure about this one
        // assuming i just call pt on each index of the runqueue?
        // Test
        long startTime = System.nanoTime();
        for (int i = 0; i < processes.size(); i++) {
            impl.precedingProcessTime(processes.get(i).getLabel());
        }
        long endTime = System.nanoTime();

        return endTime - startTime;
    }

    /**
     * Runs a particular type test on all implementations
     * @param type type to test
     * @param processes list of processes
     */
    public static void runAllImpl(String type, List<Proc> processes){
        Runqueue impl = new OrderedArrayRQ();
        runImpl(impl, type, processes);
        impl = new OrderedLinkedListRQ();
        runImpl(impl, type, processes);
        impl = new BinarySearchTreeRQ();
        runImpl(impl, type, processes);
    }

    /**
     * Runs all tests on all implementations
     * @param processes list of processes
     */
    public static void runAll(List<Proc> processes) {
        runAllImpl("en", processes);
        runAllImpl("de", processes);
        runAllImpl("pt", processes);
    }
    
    /**
     * Reports crash and quits
     */
    public static void fail(String message) {
        System.err.println("Crash!");
        System.err.println(message);

        System.exit(1);
   	 } // end of usage()
}