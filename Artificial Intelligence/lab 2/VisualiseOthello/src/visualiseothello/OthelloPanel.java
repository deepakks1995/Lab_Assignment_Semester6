/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package visualiseothello;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Stroke;
import java.awt.geom.Ellipse2D;
import java.awt.geom.Rectangle2D;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author sowmya
 */
public class OthelloPanel extends javax.swing.JPanel {
    String[] config;
    Color[][] cellData = new Color[8][8]; 
    public OthelloPanel(String[] config) {
        this.config = config;
    }
    public boolean isComplete() {
        for (int i=0; i<8; i++)
            for (int j=0; j<8; j++)
                if (cellData[i][j] != Color.BLACK && cellData[i][j] != Color.RED)
                    return false;
        return true;
    }
    public int getBlack() {
        int black = 0;
        for (int i=0; i<8; i++)
            for (int j=0; j<8; j++)
                if (cellData[i][j] == Color.BLACK)
                    black++;
        return black;
    }
    public int getRed() {
        int red = 0;
        for (int i=0; i<8; i++)
            for (int j=0; j<8; j++)
                if (cellData[i][j] == Color.RED)
                    red++;
        return red;
    }
    private void cellDataDisplay() {
       /* for (int i=0; i<8; i++) {
            for (int j=0; j<8; j++) 
                //System.out.print(cellData[i][j]+" ");
            //System.out.println("");
        }*/
                
    }
    @Override
    public void paintComponent(Graphics g) {
        Graphics2D g2 = (Graphics2D) g;
        int startX = 100, startY = 100;
        //board
        cellDataReset();
        for (int i = 0; i < 8; i++) 
            for (int j = 0; j < 8; j++) {
                int x = startX + (i * 50);
                int y = startY + (j * 50);
                Rectangle2D rect= new Rectangle2D.Double(x,y,50,50);
                g2.setStroke(new BasicStroke(3));
                g2.setColor(Color.black);
                g2.draw(rect);
                g2.setColor(Color.green);
                g2.fill(rect);
                if (i == 3 && j == 3 || i == 4 && j == 4) {
                    Ellipse2D ellipse = new Ellipse2D.Double(x+25-10, y+25-10, 20, 20);
                    g2.setColor(Color.black);
                    cellData[3][3] = cellData[4][4] = Color.black;
                    g2.draw(ellipse);
                    g2.fill(ellipse);
                }
                if (i == 3 && j == 4 || i==4 && j==3) {
                    Ellipse2D ellipse = new Ellipse2D.Double(x+25-10, y+25-10, 20, 20);
                    g2.setColor(Color.red);
                    cellData[3][4] = cellData[4][3] = Color.red;
                    g2.draw(ellipse);
                    g2.fill(ellipse);
                }
            }
        
        //config
        Color[] colors = {Color.black,Color.red};
        int index = 0;
        for (int i = 0; i < config.length && config[i] != null && !config[i].isEmpty(); i++) {
            int row = config[i].charAt(0) - 97;
            int col = config[i].charAt(1) - 48;
            if (config[i].charAt(0) == 'p') {
                index = (index + 1) % 2;
                continue;
            }
            cellData[row][col] = colors[index];
            int x = startX + (col * 50) + 25;
            int y = startY + (row * 50) + 25;
            Ellipse2D ellipse = new Ellipse2D.Double(x-10, y-10, 20, 20);
            g2.setColor(colors[index]);
            g2.draw(ellipse);
            g2.fill(ellipse);
            int j;
            for (j = col + 1; j < 8; j++) {
                if (cellData[row][j] == null)
                    break;
                if (cellData[row][j] == colors[index]) 
                    break;
            }
            for (int k = col + 1; k <= j && k < 8 && j < 8 && cellData[row][j] == colors[index] ; k++) {
                cellData[row][k] = colors[index];
                x = startX + (k * 50) + 25;
                y = startY + (row * 50) + 25;
                ellipse = new Ellipse2D.Double(x-10, y-10, 20, 20);
                g2.draw(ellipse);
                g2.fill(ellipse);
            }
            for (j = col - 1; j >= 0; j--) {
                if (cellData[row][j] == null)
                    break;
                if (cellData[row][j] == colors[index])
                    break;
            }
            for (int k = col - 1; k >= j && j>=0 && cellData[row][j] == colors[index]; k--) {
                cellData[row][k] = colors[index];
                x = startX + (k * 50) + 25;
                y = startY + (row * 50) + 25;
                ellipse = new Ellipse2D.Double(x-10, y-10, 20, 20);
                g2.draw(ellipse);
                g2.fill(ellipse);
            }
            for (j = row + 1; j < 8; j++) {
                if (cellData[j][col] == null)
                    break;
                if (cellData[j][col] == colors[index])
                    break;
            }
            for (int k = row + 1; k <= j && j<8 && cellData[j][col] == colors[index]; k++) {
                cellData[k][col] = colors[index];
                x = startX + (col * 50) + 25;
                y = startY + (k * 50) + 25;
                ellipse = new Ellipse2D.Double(x-10, y-10, 20, 20);
                g2.draw(ellipse);
                g2.fill(ellipse);
            }
            for (j = row - 1; j >= 0; j--) {
                if (cellData[j][col] == null) 
                    break;
                if (cellData[j][col] == colors[index]) 
                    break;
            }
            for (int k = row - 1; k >= j && j>=0 && cellData[j][col] == colors[index]; k--) {
                //System.out.println("hi"+k+col+colors[index]+config[i]); flag = true;
                cellData[k][col] = colors[index];
                cellDataDisplay();
                x = startX + (col * 50) + 25;
                y = startY + (k * 50) + 25;
                ellipse = new Ellipse2D.Double(x-10, y-10, 20, 20);
                g2.draw(ellipse);
                g2.fill(ellipse);
            }
            for (j = row - 1; j >= 0 && (col + row - j) < 8; j--) {
                if (cellData[j][col+row-j] == null) 
                    break;
                if (cellData[j][col+row-j] == colors[index]) 
                    break;
            }
            for (int k = row - 1; k >= j && j>=0 && (col+row-k) < 8  && (col+row-j) < 8 && cellData[j][col+row-j] == colors[index]; k--) {
                cellData[k][col+row-k] = colors[index];
                x = startX + ((col+row-k) * 50) + 25;
                y = startY + (k * 50) + 25;
                ellipse = new Ellipse2D.Double(x-10, y-10, 20, 20);
                g2.draw(ellipse);
                g2.fill(ellipse);
            }
            for (j = col - 1; j >= 0 && (j + row - col) >= 0; j--) {
                if (cellData[row+j-col][j] == null)  
                    break;
                if (cellData[row+j-col][j] == colors[index]) 
                    break;
            }
            for (int k = col - 1; k >= j && j >= 0 && (j + row - col) >= 0 && cellData[row+j-col][j] == colors[index]; k--) {
                cellData[row+k-col][k] = colors[index];
                x = startX + (k * 50) + 25;
                y = startY + ((row+k-col) * 50) + 25;
                ellipse = new Ellipse2D.Double(x-10, y-10, 20, 20);
                g2.draw(ellipse);
                g2.fill(ellipse);
            }
            for (j = col + 1; j < 8 && (j + row - col) < 8; j++) {
                if (cellData[row+j-col][j] == null) 
                    break;
                if (cellData[row+j-col][j] == colors[index]) 
                    break;
            }
            for (int k = col + 1; k <= j && j < 8 && (j + row - col) < 8 && cellData[row+j-col][j] == colors[index]; k++) {
                cellData[row+k-col][k] = colors[index];
                x = startX + (k * 50) + 25;
                y = startY + ((row+k-col) * 50) + 25;
                ellipse = new Ellipse2D.Double(x-10, y-10, 20, 20);
                g2.draw(ellipse);
                g2.fill(ellipse);
            }
            for (j = row + 1; j < 8 && (row + col -j) >= 0; j++) {
                if (cellData[j][row-j+col] == null) 
                    break;
                if (cellData[j][row-j+col] == colors[index]) 
                    break;
            }
            for (int k = row + 1; k <= j && j < 8 && (row + col -j) >= 0 && cellData[j][row-j+col] == colors[index]; k++) {
                cellData[k][row-k+col] = colors[index];
                x = startX + ((row-k+col) * 50) + 25;
                y = startY + (k * 50) + 25;
                ellipse = new Ellipse2D.Double(x-10, y-10, 20, 20);
                g2.draw(ellipse);
                g2.fill(ellipse);
            }
            cellDataDisplay();
            index = (index + 1) % 2;
        }
        //System.out.println("panel"+getRed()+"|"+getBlack());
    }

    private void cellDataReset() {
        for (int i=0; i<8; i++) 
            for (int j=0; j<8; j++) 
                cellData[i][j] = null;
    }
}