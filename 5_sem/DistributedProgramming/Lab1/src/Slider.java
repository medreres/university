import javax.swing.JSlider;

class Slider extends JSlider {
    public Slider() {
        super(0, 100);
    }

    public synchronized void increase(int increment){
        setValue(getValue() + increment);
        System.out.println(getValue());
    }
};