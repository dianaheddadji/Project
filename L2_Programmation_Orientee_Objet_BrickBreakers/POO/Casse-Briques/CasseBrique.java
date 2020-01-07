import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.Color;
import java.awt.Font;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.Graphics;
import java.awt.Graphics2D;
import javax.swing.JPanel;
import java.awt.Rectangle;
import javax.swing.Timer;


public class CasseBrique extends JPanel implements KeyListener, ActionListener{
	// KeyListener --> détecter les touches directionnelles (paddle)
	// ActionListener --> mouvements de la balle
	private int lower = 9, higher = 81, alea;
	int c, l; // Pour les loop
	boolean outsideloop = false;
	private boolean jouer = false;
	private int score = 0;
	private int scoreTotal = 0;
	private int nbPart = 1;
	private Timer timer; // Déclaration du timer pour la vitesse de déplacement de la balle
	private int frame = 6; // Valeur de la vitesse de déplacement de la balle
	private int balleDirX = -1; // Direction x de la balle
	private int balleDirY = -2; // Direction y de la balle
	private int balleX = 335; // Coordonnée x de départ de la balle
	private int balleY = 530; // Coordonnée y de départ de la balle
	private int paddlePos = 300; // Position Initial du paddle
	private Brique block; // block de briques

	public CasseBrique(){
		// Génération d'un nombre aléatoire de brique
		do{
			alea = (int) (Math.random() * (higher-lower)) + lower;
			for(c=1;  c<10; ++c){
				for(l=1; l<10; ++l)
					if((c*l)==alea){
						outsideloop = true;
						break;
					}
				if(outsideloop)
					break;
			}
		}while((c*l)!=alea);
		outsideloop = false;
		block = new Brique(c, l); // Disposition des briques
		addKeyListener(this);
		setFocusable(true);
		setFocusTraversalKeysEnabled(false);
		timer = new Timer(frame, this);
		timer.start();
	}

	public void paint(Graphics grph){
		//bg
		grph.setColor(Color.white);
		grph.fillRect(0, 0, 700, 600);

		//block de briques
		block.setBricks((Graphics2D)grph);

		//ball
		grph.setColor(Color.cyan);
		grph.fillOval(balleX, balleY, 20, 20);

		//paddle
		grph.setColor(Color.PINK);
		grph.fillRect(paddlePos, 550, 100, 5);

		//score
		grph.setColor(Color.black);
		grph.setFont(new Font("SansSerif", Font.PLAIN, 10));
		grph.drawString("Score : "+score, 590, 30);

		//score total
		grph.drawString("ScoreTotal : "+scoreTotal, 590, 45);

		// Si le joueur perd, on teste la coordonnée y de la balle
		if(balleY > 546){
			jouer = false;		
			balleDirX = 0;
			balleDirY = 0;
			grph.setColor(Color.black);
			grph.setFont(new Font ("SansSerif", 1, 20));
			grph.drawString("Perdu ! ;(", 287, 300);
			grph.setFont(new Font ("SansSerif", 0, 20));
			grph.drawString("Score : "+score, 290, 325);
			grph.drawString("Nombre de Parties : " +nbPart, 250, 370);
			grph.drawString("Score Total : "+scoreTotal, 270, 490);
			grph.setColor(Color.RED);
			grph.setFont(new Font ("serif", Font.BOLD, 15));
			grph.drawString("Appuyez sur Entrer pour rejouer", 230, 400);
		}

		// Si alea est égale à 0 c'est-à-dire, il n'y a plus de briques, le joueur gagne 
		if(alea == 0){
			jouer = false;		
			balleDirX = 0;
			balleDirY = 0;
			grph.setColor(Color.black);
			grph.setFont(new Font ("SansSerif", 1, 20));
			grph.drawString("Gagné !", 300, 300);
			grph.setFont(new Font ("SansSerif", 0, 20));
			grph.drawString("Score : "+score, 290, 325);
			grph.drawString("Nombre de Parties : " +nbPart, 250, 370);
			grph.drawString("Score Total : "+scoreTotal, 270, 490);
			grph.setColor(Color.RED);
			grph.setFont(new Font ("serif", Font.BOLD, 15));
			grph.drawString("Appuyez sur Entrer pour rejouer", 230, 400);

		}

		grph.dispose();	
	}

	/* Toutes les méthodes abstraites qui résident dans les interfaces doivent être implémentées à l'intérieur de la classe qui implémente KeyListener et ActionListener */

	// Ajout des méthodes requises pour KeyListener
	@Override
	public void keyPressed(KeyEvent event){
		if(event.getKeyCode() == KeyEvent.VK_LEFT){
			if(paddlePos <= 1)
				paddlePos = 1;
			else
				toLeft();
		}

		if(event.getKeyCode() == KeyEvent.VK_RIGHT){
			if(paddlePos >= 599)
				paddlePos = 599;
			else
				toRight();
		}
		
		// Si le joueur appuie sur entrer
		if(event.getKeyCode() == KeyEvent.VK_ENTER){
			// Et que le jeu est terminé
			if(!jouer){
				// On redessine le jeu avec un nouveau block de briques
				do{
					alea = (int) (Math.random() * (higher-lower)) + lower;
					for(c=1;  c<10; ++c){
						for(l=1; l<10; ++l)
							if((c*l)==alea){
								outsideloop = true;
								break;
							}
						if(outsideloop)
							break;
					}
				}while((c*l)!=alea);
				outsideloop = false;
				block = new Brique(c, l);
				jouer = true;
				balleDirX = -1;
				balleDirY = -2;
				balleX = 100;
				balleY = 300;
				paddlePos = 300;
				++nbPart;
				score = 0;
				repaint();
			}
		}		
	}

	@Override
	public void keyTyped(KeyEvent event){}

	@Override
	public void keyReleased(KeyEvent event){}

	// Ajout de la méthode requise pour ActionListener
	@Override
	public void actionPerformed(ActionEvent event){
		timer.start();
		if(jouer){
			// Collision entre la balle et le paddle
			// On crée un nouveau rectangle autour de la balle
			// et on teste la valeur retournée par intersects pour savoir si une collision entre les deux rectangles (paddle\balle) a lieu
			if(new Rectangle(balleX, balleY, 20, 20).intersects(new Rectangle(paddlePos, 550, 100, 5)))
				balleDirY = -balleDirY; // balle rebondit
			 COL : for(int i = 0; i < block.block.length; i++)
				for(int j = 0; j < block.block[0].length; j++)
					// Si dans une position donnée, le marqueur est plus grand que 0, on détecte l'intersection (balle-brique) pour cela, on a besoin de connaître la position de la balle et la position de la ou des brique(s) 
					if(block.block[i][j] > 0){
						// Conversion pour connaître les "vraies" coordonnées des briques
						int briqueX = j * block.briqueW + 80;
						int briqueY = i * block.briqueH + 50;
						int briqueW = block.briqueW;
						int briqueH = block.briqueH;
				
						// Création des rectangles autour des briques
						Rectangle rectangle = new Rectangle(briqueX, briqueY, briqueW, briqueH);
						// Création d'un rectangle autour de la balle
						Rectangle balleRectangle = new Rectangle(balleX, balleY, 20, 20);
						Rectangle briqueRectangle = rectangle;
						
						// Collision entre la balle et la/les brique(s)
						// Pour cela, nous avons besoin d'appeler la fonction briqueState et de changer la valeur contenue dans block[l][c] à 0
						if(balleRectangle.intersects(briqueRectangle)){
							block.briqueState(i, j, 0);
							alea--;
							score += 5;
							scoreTotal += 5;

							// Pour l'intersection droite ou gauche
							if(balleX + 1 >= briqueRectangle.x + briqueRectangle.width || balleX + 19 <= briqueRectangle.x)
								balleDirX = -balleDirX; // On déplace la balle dans la direction opposée
							else
								balleDirY = -balleDirY;
							break COL;
						}
					}
			
			// Pour faire avancer la balle
			balleX += balleDirX;
			balleY += balleDirY;
			// Si la balle touche les axes
			if(balleX < 0)
				balleDirX = -balleDirX;
			if(balleY < 0)
				balleDirY = -balleDirY;
			if(balleX > 680)
				balleDirX = -balleDirX;
		}
		repaint();
	}

	// Procédures déterminant les valeurs de déplacement du paddle (Droite/Gauche)
	public void toLeft(){
		paddlePos -= 35; // Déplacement de 30 pixels vers la gauche 
		jouer = true; // On s'assure à ce que jouer soit à true
	}

	public void toRight(){
		paddlePos += 35; // Déplacement de 30 pixels vers la droite 
		jouer = true;
	}
}
