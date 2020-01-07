//Les Fonctions

//chargement_image
function [image,S] = chargement_image(formats,handle)
	image = imread(uigetfile(formats,"$HOME","Charger une image"));
	S = image;
	imshow(S);
    handle.S = S;
    handle = resume(handle);
endfunction

//etaler_filtre
function [N] = etaler_filtre(filterlist,handle)
    if filterlist.Value ==1 then
		N = canny(handle.S);
		imshow(N);
        handle.N = N;
        handle =resume(handle); 
		end
    if filterlist.Value ==2 then
		N = bonus(handle.S);
		imshow(N);
        handle.N = N;
        handle =resume(handle); 
		end
    if filterlist.Value ==3 then
		N = horizontal(handle.S);
		imshow(N);
        handle.N = N;
        handle =resume(handle); 
		end
    if filterlist.Value ==4 then
		N = vertical(handle.S);
		imshow(N);
        handle.N = N;
        handle =resume(handle); 
		end
    if filterlist.Value ==5 then
		N = horivertical(handle.S);
		imshow(N);
        handle.N = N;
        handle =resume(handle);
		end
    if filterlist.Value ==6 then
		N = gaussien(handle.S);
		imshow(N);
        handle.N = N;
        handle =resume(handle);
		end
    if filterlist.Value ==7 then
		N = nb(handle.S);
		imshow(N);
        handle.N = N;
        handle =resume(handle); 
		end
    if filterlist.Value ==8 then
		N = negatif(handle.S);
		imshow(N);
        handle.N = N;
        handle =resume(handle);
		end
    if filterlist.Value ==9 then
		N = prewitt(handle.S);
		imshow(N);
        handle.N = N;
        handle =resume(handle);
		end
    if filterlist.Value ==10 then
		N = sobel(handle.S);
		imshow(N);
        handle.N = N;
        handle =resume(handle);
		end
    if filterlist.Value ==11 then
		N = red(handle.S);
		imshow(N);
        handle.N = N;
        handle =resume(handle);
		end
    if filterlist.Value ==12 then
		N = green(handle.S);
		imshow(N);
        handle.N = N;
        handle =resume(handle);
		end
    if filterlist.Value ==13 then
		N = blue(handle.S);
		imshow(N);
        handle.N = N;
        handle =resume(handle);
		end
    if filterlist.Value ==14 then
		N = cyan(handle.S);
		imshow(N);
        handle.N = N;
        handle =resume(handle);
		end
    if filterlist.Value ==15 then
		N = yellow(handle.S);
		imshow(N);
        handle.N = N;
        handle =resume(handle);
		end
    if filterlist.Value ==16 then
		N = purple(handle.S);
		imshow(N);
        handle.N = N;
        handle =resume(handle);
		end
endfunction

//cleaner_picture
function [image] = cleaner_picture(handle)
     image = handle.S;
     imshow(image); 
endfunction

//sauvegarder_image
function [] = sauvegarder_image(formats,handle)
	imwrite(handle.N, uiputfile(formats,"C:\Users\hedda\Pictures","Sauvegarder"));
endfunction
