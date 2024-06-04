import javax.swing.SpinnerModel;
import javax.swing.JSpinner;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.SpinnerNumberModel;

class SliderThread extends Thread {
    private int increment;
    private Slider mySlider;
    private static int THREAD_COUNTER = 0;
    private int curNum;
    private static int BOUND = 100000;

    private int count;

    public SliderThread(Slider mySlider, int increment, int priority) {
        this.mySlider = mySlider;
        this.increment = increment;
        curNum = ++THREAD_COUNTER;
        setPriority(priority);
    }

    @Override
    public void run() {
        while(!interrupted()){
            int val = (int)(mySlider.getValue());
            ++count;
            if(count > BOUND){
                mySlider.increase(increment);
                count = 0;
            }
        }
    }

    public JPanel GetJPanel() {
        JPanel panel = new JPanel();
        JLabel label = new JLabel("Thread #" + curNum + ", Increment = " + increment);
        SpinnerModel sModel = new SpinnerNumberModel(this.getPriority(), Thread.MIN_PRIORITY, Thread.MAX_PRIORITY, 1);
        JSpinner Spinner = new JSpinner(sModel);
        Spinner.addChangeListener(e->{
            System.out.println("Priortiy of" + (int)(Spinner.getValue()));
            setPriority((int)(Spinner.getValue()));
        });
        panel.add(label);
        panel.add(Spinner);
        return panel;
    }
}