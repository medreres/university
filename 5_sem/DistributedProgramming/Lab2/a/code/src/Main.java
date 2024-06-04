import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicInteger;

public class Main {
    private boolean[][] forest;
    private final AtomicBoolean founded;
    private final AtomicInteger currentRow;
    private final Integer SIZE_OF_FOREST;
    public final Integer COUNT_OF_THREADS;
    private Thread[] threads;
    private class Bees extends Thread {
        public Bees(){}

        public void run() {
            while(!founded.get() && currentRow.get() < SIZE_OF_FOREST) {
                isPoohInRow(currentRow.get());
                currentRow.set(currentRow.get() + 1);
            }
        }
    }
    public Main(Integer SIZE_OF_FOREST) {
        this.SIZE_OF_FOREST = SIZE_OF_FOREST;
        this.COUNT_OF_THREADS = (int)Math.sqrt(SIZE_OF_FOREST);
        this.threads = new Thread[COUNT_OF_THREADS];
        forest = new boolean[SIZE_OF_FOREST][SIZE_OF_FOREST];

        // Initialize matrix
        for(int i = 0; i < SIZE_OF_FOREST; i++){
            for(int j = 0; j < SIZE_OF_FOREST; j++) {
                forest[i][j] = false;
            }
        }

        // Randomly place Pooh
        int column = (int)(Math.random() * SIZE_OF_FOREST);
        int row = (int)(Math.random() * SIZE_OF_FOREST);
        System.out.println("Pooh is in row: " + row + " column: " + column);
        forest[row][column] = true;

        founded = new AtomicBoolean(false);
        currentRow = new AtomicInteger(0);
    }
    private void checkAllForest(){
        for(int i = 0; i < COUNT_OF_THREADS; i++){
            threads[i] = new Bees();
            threads[i].start();
        }
        for(int i = 0; i < COUNT_OF_THREADS; i++){
            try{
                threads[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
    private void isPoohInRow(int row) {
        if(founded.get()) { return; }

        System.out.println(Thread.currentThread().getName() + " group of bees in row: " + row);
        for(int i = 0; i < SIZE_OF_FOREST; i++) {
            if(!forest[row][i]){
               continue;
            }

            System.out.println(Thread.currentThread().getName() + " pooh was founded in row: " + row + " column " + i);
            founded.set(true);
            break;
        }
    }
    public static void main(String[] args) {
        Main BeesFindingWinniePooh = new Main(100);
        BeesFindingWinniePooh.checkAllForest();
    }
}
