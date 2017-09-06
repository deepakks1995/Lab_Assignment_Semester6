/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package visualiseothello;

import java.awt.Color;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.Timer;
//import static visualizer.OthelloPanel.cellData;

/**
 *
 * @author sowmya
 */
public class VisualizeOthello extends javax.swing.JFrame {
    /**
     * @param args the command line arguments which are ignored
     */
    static int counter = 0;
    static String[] moves = new String[200];
    static int max = 0;
    static OthelloPanel op = new OthelloPanel(new String[]{""});
    static JTextField blackValue = new JTextField(5);
    static JTextField redValue = new JTextField(5);
    static JTextField blackFileName = new JTextField(20);
    static JTextField redFileName = new JTextField(20);  
    static Timer t = new Timer(1000, new ActionListener() {

        @Override
        public void actionPerformed(ActionEvent ae) {
            if (op.isComplete()) {
                showResult = true;
                counter--;
                return;
            }
            String[] temp = new String[counter];
            System.arraycopy(moves, 0, temp, 0, counter);
            op.config = temp;
            op.repaint();
            counter++;    
            
        }
        
    });
    static boolean showResult = false;
    public static void main(String[] args) throws InterruptedException {
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException ex) {
        } catch (InstantiationException ex) {
        } catch (IllegalAccessException ex) {
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
        }
        VisualizeOthello v = new VisualizeOthello();
        GridLayout layout = new GridLayout(1,2);
        //layout.setHgap(10);
        v.setLayout(layout);
        v.setExtendedState(v.getExtendedState() | JFrame.MAXIMIZED_BOTH);
        v.setTitle("Othello Visualizer");
        
        v.add(op);
        GridLayout inlayout = new GridLayout(4,2);
        inlayout.setHgap(50);
        inlayout.setVgap(50);
        JPanel details = new JPanel();
        details.setLayout(inlayout);
        details.add(new JLabel("Black: "));
        details.add(blackValue);
        details.add(new JLabel("Red: "));
        details.add(redValue);
        redValue.setText("2");
        blackValue.setText("2");
        
        JButton prev = new JButton("Previous");
        JButton next = new JButton("Next");
        details.add(prev);
        details.add(next);
        
        JButton play = new JButton("Play");
        JButton reset = new JButton("Reset");
        details.add(play);
        details.add(reset);
        v.add(details);
        v.setVisible(true);
        v.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        
        int i = 0;
        try (BufferedReader br = new BufferedReader(new FileReader(new File("game.log")))) {
            String line;
            while ((line = br.readLine()) != null) {
                moves[i] = line;
                i++;
            }
        } catch (Exception e) {
            
        }
        max = i;
        play.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent ae) {
                    counter = 0;
                    t.start();
                    
                }
                
            });
        
        reset.addActionListener(new ActionListener() {

            @Override
            public void actionPerformed(ActionEvent ae) {
                counter = 0;
                op.config = new String[]{""};
                op.repaint();
            }
            
        });
        prev.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent ae) {
                if (counter == 0)
                    JOptionPane.showMessageDialog(null, "Cannot go to previous move: Initial State");
                else {
                    counter--;
                    String[] temp = new String[counter];
                    for (int j=0; j<counter; j++)
                        temp[j] = moves[j];
                    op.config = temp;
                    op.repaint();op.repaint();
                }
            }
            
        });
        next.addActionListener(new ActionListener() {

            @Override
            public void actionPerformed(ActionEvent ae) {
                //redValue.setText(op.getRed()+"");
                //blackValue.setText(op.getBlack()+"");
               
                if (counter == max)
                    JOptionPane.showMessageDialog(null, "Cannot go to next move: Final State");
                else {
                    counter++;
                    String[] temp = new String[counter];
                    System.arraycopy(moves, 0, temp, 0, counter);
                    op.config = temp;
                    op.repaint();
                    if (counter == max)
                        showResult = true;       
                }
                
            }
            
        });
        while(true) {
            redValue.setText(op.getRed()+"");
            blackValue.setText(op.getBlack()+""); 
            if (showResult) {
                if (!op.isComplete())
                    continue;
                if (t.isRunning())
                    t.stop();
                int black = op.getBlack();
                int red = op.getRed();
                if (black > red)
                    JOptionPane.showMessageDialog(null, "Black Wins!");
                else if (red > black)
                    JOptionPane.showMessageDialog(null, "Red Wins!");
                else
                    JOptionPane.showMessageDialog(null, "Draw");
                showResult = false;
            }
        }
        
    }
    
}