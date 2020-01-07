# -*- coding: cp1252 -*-

import math
import random

# ouvrir

TD = open("iris_test_data", "r")
TL = open("iris_test_label", "r")
LD = open("iris_learn_data", "r")
LL = open("iris_learn_label", "r")

# d(u,v) = sqrt((x1-x2)^2+(y1-y2)^2+(z1-z2)^2+(t1-t2)^2)



def liste_charverint (t, *liste):
    listrep = []
    i=0
    inter = liste[i]
    while (i<t):
        listrep.append ((float)(inter[i]))
        i+=1
    return listrep



def taux_juste_kppv (k):
    i = 0
    dev = []
    TD.seek(0)
    TL.seek(0)
    while (i<10):
        ppvD = []
        ppvN = []
        ppvL = []
        lTD = TD.readline()
        lTD = lTD.split(";")
        lTD = liste_charverint(4, lTD)
        # remplissage de base.
        while (len(ppvD) < k):
            n = 1
            nn = 0
            ll = 0
            mini = 0
            LD.seek(0)
            LL.seek(0)
            while (n<=140):
                if n not in ppvN :
                    lLD = LD.readline()
                    lLL = LL.readline()
                    lLD = lLD.split(";")
                    lLL = lLL.split(";")
                    lLD = liste_charverint(4, lLD)
                    lLL = liste_charverint(1, lLL)
                    d = math.sqrt((lTD[0]-lLD[0])**2+(lTD[1]-lLD[1])**2+(lTD[2]-lLD[2])**2+(lTD[3]-lLD[3])**2)
                    #print(d)
                    if mini == 0 :
                        mini = d
                        nn = n
                        la = lLL[0]
                    elif d < mini :
                        mini = d
                        nn = n
                        la = lLL[0]
                else :
                    lLD = LD.readline()
                    lLL = LL.readline()                    
                n+=1
            #print(mini)
            #print(nn)
            #print(la)
            ppvD.append(mini)
            ppvN.append(nn)
            ppvL.append(la)
        #print (ppvD)
        #print (ppvN)
        #print (ppvL)
        # ajout des éventuelles distances équivalentes au k plus éloigné (Cas de points équidistants).
        n = 1
        LD.seek(0)
        LL.seek(0)
        while (n<=140):
            lLD = LD.readline()
            lLL = LL.readline()
            lLD = lLD.split(";")
            lLL = lLL.split(";")
            lLD = liste_charverint(4, lLD)
            lLL = liste_charverint(1, lLL)
            la = lLL[0]
            d = math.sqrt((lTD[0]-lLD[0])**2+(lTD[1]-lLD[1])**2+(lTD[2]-lLD[2])**2+(lTD[3]-lLD[3])**2)
            if (d == ppvD[k-1]) and (n not in ppvN) :
                ppvD.append(d)
                ppvN.append(n)
                ppvL.append(la)
            n+=1
        #print (ppvD)
        #print (ppvN)
        #print (ppvL)
        # calcul de la classe
        c0 = ppvL.count(0)
        c1 = ppvL.count(1)
        c2 = ppvL.count(2)
        #print(c0,c1,c2)
        if c0 > c1 and c0 > c2 :
            dev.append(0)
        elif c1 > c0 and c1 > c2 :
            dev.append(1)
        elif c2 > c0 and c2 > c1 :
            dev.append(2)
        elif c0 == c1 and c0 > c2 :
            x = random.randint(0, 1)
            dev.append(x)
        elif c0 == c2 and c0 > c1 :
            x = random.randint(0, 1)
            if x == 1 :
                x = 2
            dev.append(x)
        elif c1 == c2 and c1 > c0 :
            x = random.randint(1, 2)
            dev.append(x)
        elif c0 == c1 and c0 == c2 :
            x = random.randint(0, 2)
            dev.append(x)    
        i+=1
    #print (dev)
    # taux de bonne classification
    i = 0
    just = 0.0
    while (i<10):
        lTL = TL.readline()
        lTL = lTL.split(";")
        lTL = liste_charverint(1, lTL)
        if lTL[0] == dev[i]:
            just+=1
        i+=1
    taux = just/10
    #print (taux)
    return taux



k = 2
ltaux = []
while (k<=10):
    t = taux_juste_kppv(k)
    ltaux.append(t)
    print ('pour k = ' + repr(k) + ' le taux de bonne classification est de : ' + repr(t))
    k+=1
print(ltaux)





