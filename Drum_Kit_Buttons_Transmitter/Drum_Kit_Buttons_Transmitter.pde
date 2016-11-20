import java.awt.event.KeyEvent;
import javax.swing.JOptionPane;
import processing.serial.*;
import processing.opengl.*;

Serial port = null;
String portname = null;

void setup() {
  size(150, 100);
  openSerialPort();
  selectSerialPort();
  //delay(3000);
}

void draw() {
  //background(0);
}

void openSerialPort()
{
  if (portname == null) return;
  if (port != null) port.stop();
  port = new Serial(this, portname, 115200);
  port.bufferUntil('\n');
}

void selectSerialPort()
{
  String result = (String) JOptionPane.showInputDialog(this, 
  "Select the serial port that corresponds to your Arduino board.", 
  "Select serial port", 
  JOptionPane.PLAIN_MESSAGE, 
  null, 
  Serial.list(), 
  0);

  if (result != null) {
    portname = result;
    openSerialPort();
  }
}



void keyPressed() {
  if (key == 'k') {
    port.write('k');
  }
  if (key == 'd') {
    port.write('d');
  }
  if (key == 't') {
    port.write('t');
  }
}

