function cny =canny(image)
  image = nb(image)
  cny = edge(image,'canny')
endfunction

function y = bonus(x)
    [nl,nc]=size(x)
    y = [];
    for i=2:nl-1
        for j=2:nc-1
            y(i,j)=(x(i,j)+x(i+1,j+1)-x(i,j+1)-x(i-1,j+1)-x(i+1,j)-x(i-1,j)-x(i+1,j-1)-x(i,j-1)-x(i-1,j-1))
        end
    end
endfunction

function flou = gaussien(image)
  G = fspecial('gaussian',27,3);
  flou = imfilter(image,G);
endfunction

function hrztl = horizontal(image)
     [x,y,c] = size(image)
     for i = 1 : x/2+1
        for j = 1 : y
            hrztl(i,j,:) = matrix(image(x-i+1,j,:),1,c)
            hrztl(x-i+1,j,:) = matrix(image(i,j,:),1,c)
        end 
     end
endfunction

function hv = horivertical(image)
     [x,y,c] = size(image)
     for i=1:x
        for j=1:y/2+1
            hv(i,j,:)=matrix(image(x-i+1, y-j+1,:),1,3)
            hv(x-i+1, y-j+1,:)=matrix(image(i,j,:),1,3)
        end
     end
endfunction

function vrtcl = vertical(image)
    [x,y,c] = size(image)
    for i = 1 : x
       for j = 1 : y/2+1
          vrtcl(i,j,:) = matrix(image(i,y-j+1,:),1,c)
          vrtcl(i,y-j+1,:) = matrix(image(i,j,:),1,c)
       end
    end
endfunction

function img = nb(image)
	r = image(:,:,1)
	g = image(:,:,2)
	b = image(:,:,3)
	img = imlincomb(0.299,r,0.587,g,0.114,b)
endfunction

function ngtf = negatif(image)
  ngtf = 255 - image
endfunction

function prwt =prewitt(image)
  image = nb(image)
  prwt = edge(image,'prewitt')
endfunction

function sbl =sobel(image)
  S = fspecial('sobel');
  sbl = imfilter(image,S);
endfunction

function rouge =red(image)
  Blanc = uint8(zeros(image(:,:,1)))
	rouge = image(:,:,1)
	rouge(:,:,2) = Blanc
	rouge(:,:,3) = Blanc
endfunction

function vert =green(image)
  Blanc = uint8(zeros(image(:,:,1)))
	vert(:,:,1) = Blanc
	vert(:,:,2) = image(:,:,2)
	vert(:,:,3) = Blanc
endfunction

function bleu =blue(image)
  Blanc = uint8(zeros(image(:,:,1)))
	bleu(:,:,1)= Blanc
	bleu(:,:,2)= Blanc
	bleu(:,:,3)= image(:,:,3)
endfunction

function cyn =cyan(image)
  Blanc = uint8(zeros(image(:,:,1)))
	cyn(:,:,1) = Blanc
	cyn(:,:,2) = image(:,:,2)
	cyn(:,:,3) = image(:,:,1)
endfunction

function violet =purple(image)
  Blanc = uint8(zeros(image(:,:,1)))
	violet(:,:,1) = image(:,:,1)
	violet(:,:,2) = Blanc
	violet(:,:,3) = image(:,:,1)
endfunction

function jaune =yellow(image)
  Blanc = uint8(zeros(image(:,:,1)))
	jaune(:,:,1) = image(:,:,1)
	jaune(:,:,2) = image(:,:,1)
	jaune(:,:,3) = Blanc
endfunction
