/* 
	 Projet POO Java Casse-Brique 
	 Diana Heddadji
   16712076
   Etudiante L2/L3 Informatique 
   Paris 8
*/

//Exécuter avec java Main

import javax.swing.JFrame; // package permettant d'utiliser la classe JFrame

public class Main{

	public static void main(String[] args){
		JFrame jfApp = new JFrame();
		CasseBrique casseBrique = new CasseBrique(); // Création de l'objet CasseBrique afin de l'ajouter à l'ojet jfApp
		// Déclaration des propriétés de jfApp
		jfApp.setBounds(500, 100, 700, 600); // Disposition du background
		jfApp.setTitle("Casse-Brique"); // Titre
		jfApp.setResizable(false); // Pas de redimension manuelle
		jfApp.setVisible(true); // Afficher la fenêtre
		jfApp.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); // Fermer proprement le programme
		jfApp.add(casseBrique);
	}

}
