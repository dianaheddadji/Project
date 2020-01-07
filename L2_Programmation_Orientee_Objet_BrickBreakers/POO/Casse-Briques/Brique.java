import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics2D;


public class Brique{
	// Coordonnées des briques
	public int briqueH;
	public int briqueW;
	public int block[][]; // Conteneur de briques

	public Brique(int colonne, int ligne){
		briqueW = 540/colonne;
		briqueH = 150/ligne;
		block = new int[ligne][colonne];
		// Génération des rangés de briques
		for(int l = 0; l < block.length; ++l)
			for(int c = 0; c < block[0].length; ++c)
				block[l][c] = 1; // On initialise toutes les briques avec un marqueur égale à 1 pour indiquer que les briques n'ont pas été cassées
	}

	// Fonction qui change le marqueur de la brique en cas de collision
	public void briqueState(int ligne, int colonne, int val){
		block[ligne][colonne] = val;
	}


	// Cette fonction dessinera toutes les briques dont le marqueur est égale à 1	
	public void setBricks(Graphics2D grph){
		for(int l = 0; l < block.length; ++l)
			for(int c = 0; c < block[0].length; ++c)
				if(block[l][c] > 0){
					grph.setColor(Color.black);
					grph.fillRect(c * briqueW + 80, l * briqueH + 50, briqueW, briqueH);		
					grph.setStroke(new BasicStroke(1)); // Pour séparer chaque colonne
					grph.setColor(Color.white);
					grph.drawRect(c * briqueW + 80, l * briqueH + 50, briqueW, briqueH);		
				}
	}
	
}
