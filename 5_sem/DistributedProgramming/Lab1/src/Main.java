import javax.swing.JFrame;
import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.BoxLayout;

public class Main {
    public static void main(String[] args) {
        JFrame myFrame = new JFrame();
        myFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        myFrame.setSize(500, 500);
        Slider slider = new Slider();

        SliderThread thread1 = new SliderThread(slider, +1, Thread.NORM_PRIORITY);
        SliderThread thread2 = new SliderThread(slider, -1, Thread.NORM_PRIORITY);

        JButton startBtn = new JButton("Start");
        startBtn.addActionListener(e -> {
            thread1.start();
            thread2.start();
            startBtn.setEnabled(false);
        });
        JPanel myPanel = new JPanel();
        myPanel.setLayout(new BoxLayout(myPanel, BoxLayout.Y_AXIS));

        myPanel.add(thread1.GetJPanel());
        myPanel.add(thread2.GetJPanel());
        myPanel.add(slider);

        JPanel jPanel = new JPanel();
        jPanel.add(startBtn);
        myPanel.add(jPanel);

        myFrame.setContentPane(myPanel);
        myPanel.setVisible(true);
    }
}