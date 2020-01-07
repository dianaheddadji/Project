//Configuration
formats = ["JPG/JPEG format","*.jp*g";"*.png","PNG format"];
window = figure();
window.background = color(50, 50, 50);
window.figure_name = gettext("MyPhotoshop Cc");

handle.Axesl = newaxes();
handle.Axesl.margins = [0 0 0 0];
handle.Axesl.axes_bounds = [0.05, 0.2, 0.66, 0.5];
handle.Axesl.background = color(30, 30, 30);
handle.Axesl.auto_clear = 'on';

//Création d'un module pour charger l'image via chargement_image
h1= uimenu("parent",window,"label",gettext("Charger une image"),"callback","chargement_image(formats)");

//Cacher les menu
delmenu(window.figure_id,gettext("&File"));
delmenu(window.figure_id,gettext("&Tools"));
delmenu(window.figure_id,gettext("&Edit"));
delmenu(window.figure_id,gettext("&?"));
delmenu(window.figure_id,gettext("off"));

//Textes

//Photoshop CC
photoshopCc = uicontrol(window,"style","text");
photoshopCc.string = "Photoshop CC";
photoshopCc.fontweight = "bold";
photoshopCc.position = [160 370 150 25];
photoshopCc.BackgroundColor = [0.20 0.20 0.20];
photoshopCc.ForegroundColor = [1 0 0.4];
photoshopCc.HorizontalAlignment = "center";

//Filtres
filtres = uicontrol(window,"style","text");
filtres.string = "Filtres";
filtres.fontweight = "bold";
filtres.position = [448 320 130 25];
filtres.BackgroundColor = [0.12 0.12 0.12];
filtres.ForegroundColor = [1 0 0.4];
filtres.HorizontalAlignment = "center";

//La Filtre Box
filtres_box=uicontrol(window,"style","listbox");
filtres_box.BackgroundColor=[0.12 0.12 0.12];
filtres_box.ForegroundColor=[0.25 0.25 0.25];
filtres_box.Position = [448 170 130 150];
filtres_box.String = ["Canny","Bonus","Horizontal","Vertical","Horivertical","Gaussien","N/B","Negatif","Prewitt","Sobel","Rouge","Vert","Bleu", "Cyan","Jaune","Violet"];
filtres_box.Value = 1;

//Les bouttons

//quitter
quitter = uicontrol(window,"style","pushbutton");
quitter.String = "Quitter";
quitter.BackgroundColor=[0.12 0.12 0.12];
quitter.ForegroundColor=[1 0 0.4];
quitter.Position = [28 75 130 50];
quitter.Callback = "delete(window)";

//cleaner
cleaner = uicontrol(window,"style","pushbutton");
cleaner.String = "Cleaner";
cleaner.BackgroundColor=[0.12 0.12 0.12];
cleaner.ForegroundColor=[1 0 0.4];
cleaner.Position = [168 75 130 50];
cleaner.Callback = "[current_ns_image] = cleaner_picture(handle);";

//sauvegarder
sauvegarder = uicontrol(window,"style","pushbutton");
sauvegarder.String = "Sauvegarder";
sauvegarder.BackgroundColor=[0.12 0.12 0.12];
sauvegarder.ForegroundColor=[1 0 0.4];
sauvegarder.Position = [308 75 130 50];
sauvegarder.Callback = "sauvegarder_image(formats,handle)";

//etaler
etaler = uicontrol(window,"style","pushbutton");
etaler.String = "Étaler";
etaler.BackgroundColor=[0.12 0.12 0.12];
etaler.ForegroundColor=[1 0 0.4];
etaler.Position = [448 75 130 50];
etaler.Callback = "[current_s_image] = etaler_filtre(filtres_box,handle)";
