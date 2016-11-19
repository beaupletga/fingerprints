#!/usr/bin/env python
# -*- coding: utf-8 -*-
#sudo apt-get install python-imaging-tk
#sudo apt-get install python-tk
import os
import Tkinter
import tkFileDialog
import ttk
import glob
from Tkinter import *
import PIL
from PIL import ImageTk, Image
from decimal import Decimal

commande = "g++-5 -std=c++1y -o prog -Wall -Wextra -Weffc++ -pedantic -Wl,-rpath,. main.cc libeistipng.so"
os.system(commande)


window = Tk()
global canvas
canvas = Canvas(window, width=1920, height=800)
canvas.pack(side=BOTTOM)



global min_legal
min_legal=12#nombre de minuties minimal


def changer():#changer le nombre de minuties minimal
    global min_legal
    min_legal=int(e1.get())


def changer_min_legal():
    global e1

    master = Toplevel()
    Label(master, text="Minuties Nécessaires").grid(row=0)

    e1 = Entry(master)
    e1.grid(row=0, column=1)

    Button(master, text='Quit', command=master.quit).grid(row=3, column=0, sticky=W, pady=4)
    Button(master, text='Valider', command=changer).grid(row=3, column=1, sticky=W, pady=4)
    master.mainloop()




def recup(chaine):
    img=""
    for i in range(len(chaine)-1,1,-1):
        img=chaine[i]+img
        if (chaine[i-1]=='/'):
            return img


def bifurc(entier):#affiche les bifurcations des deux empreintes
    popo=Toplevel()
    if entier==1:
        img1 = ImageTk.PhotoImage(Image.open('disp_bifurcation1.png'))
        panel1 = Label(popo, image = img1,width=300, height=300)
        panel1.pack(side = "left",expand="yes", fill = "both",padx=10, pady=10)
    if entier==2:
        img2 = ImageTk.PhotoImage(Image.open('disp_bifurcation2.png'))
        panel2 = Label(popo, image = img2,width=300, height=300)
        panel2.pack(side = "left",expand="yes", fill = "both",padx=10, pady=10)

    popo.title("Details du processus")
    popo.geometry("1920x1920")
    popo.configure(background='grey')
    popo.mainloop()

def squelette(entier):#affiche dans une nouvelle fenetre la squelettisation et le filtre median de l'empreinte
    popo=Toplevel()
    if entier==1:
        img1 = ImageTk.PhotoImage(Image.open('filtre_median1.png'))
        img2 = ImageTk.PhotoImage(Image.open("bifurcation1.png"))
        panel1 = Label(popo, image = img1,width=300, height=300)
        panel2 = Label(popo, image = img2,width=300, height=300)
        panel1.pack(side = "left",expand="yes", fill = "both",padx=10, pady=10)
        panel2.pack(side = "right",expand="yes", fill = "both",padx=10, pady=10)
    if entier==2:
        img1 = ImageTk.PhotoImage(Image.open('filtre_median2.png'))
        img2 = ImageTk.PhotoImage(Image.open("bifurcation2.png"))
        panel1 = Label(popo, image = img1,width=300, height=300)
        panel2 = Label(popo, image = img2,width=300, height=300)
        panel1.pack(side = "left",expand="yes", fill = "both",padx=10, pady=10)
        panel2.pack(side = "right",expand="yes", fill = "both",padx=10, pady=10)

    popo.title("Details du processus")
    popo.geometry("1920x1920")
    popo.configure(background='grey')
    popo.mainloop()

def tout():#compare deux empreintes (mode 1)
    canvas.delete("all")
    window.title("Comparer deux empreintes")
    filepath1 = tkFileDialog.askopenfilename(title="Choisir la première image",filetypes=[('png files','.png'),('all files','.*')])
    filepath2 = tkFileDialog.askopenfilename(title="Choisir la deuxième image",filetypes=[('png files','.png'),('all files','.*')])
    commande1 = "./prog "+filepath1 +" 1"
    commande2= "./prog "+filepath2 +" 2"

    pb = ttk.Progressbar(window, orient="horizontal", length=200,mode="determinate")
    pb.pack()
    pb.step(5)

    window.update()
    os.system(commande1)
    os.system(commande2)

    pb.step(90)
    window.update()
    path1 =filepath1
    path2 =filepath2

    filename1 = PhotoImage(file = path1)
    img1 = canvas.create_image(400, 350, image=filename1)
    canvas.pack(expand="yes", fill = "both",padx=10, pady=10)
    filename2 = PhotoImage(file = path2)
    img2 = canvas.create_image(1500, 350,image=filename2)
    canvas.pack(expand="yes", fill = "both",padx=10, pady=10)


    button1 = Button(canvas,text="Afficher la squelettisation",command=lambda : squelette(1),bd=5, anchor = W)
    button1.configure()
    button1_window = canvas.create_window(400, 10, anchor=N, window=button1)

    button2 = Button(canvas,text="Afficher la squelettisation",command=lambda : squelette(2),bd=5, anchor = W)
    button2.configure()
    button2_window = canvas.create_window(1500, 10, anchor=N, window=button2)

    button3 = Button(canvas,text="Afficher les bifurcations",command=lambda : bifurc(1),bd=5, anchor = W)
    button3.configure()
    button3_window = canvas.create_window(400, 50, anchor=N, window=button3)

    button4 = Button(canvas,text="Afficher les bifurcations",command=lambda : bifurc(2),bd=5, anchor = W)
    button4.configure()
    button4_window = canvas.create_window(1500, 50, anchor=N, window=button4)

    pb.pack_forget()
    #window.mainloop()


    commande="g++-5 fonctions.cpp -o fonctions"
    os.system(commande)
    commande="./fonctions"
    os.system(commande)


    fichier = open("resultat.txt", "r")
    lignes=fichier.read()
    fichier.close()
    #os.system("rm ratio1.txt ratio2.txt")
    #os.system("rm resultat.txt")

    global match
    tmp=int(lignes)
    if (tmp>=min_legal):
        text1=canvas.create_text(950,600,text="Match : "+"100%",fill="red",font=("Geneva",21))
    if ((tmp>7)and(tmp<min_legal)):
        text2=canvas.create_text(950,600,text="Match : "+str((tmp*100)/min_legal)+"%",fill="red",font=("Geneva",21))
    if(tmp<=7):
        text3=canvas.create_text(950,600,text="No Match : "+str((tmp*100)/min_legal)+"%",fill="red",font=("Geneva",21))

    window.mainloop()


def repertoire():#compare une empreinte avec un repertoire (mode 2)
    canvas.delete("all")
    window.title("Comparer une empreinte avec un repertoire")
    filepath = tkFileDialog.askopenfilename(title="Ouvrir une image",filetypes=[('png files','.png'),('all files','.*')])
    repertoire_str=tkFileDialog.askdirectory(title="Choisir un repertoire")

    repertoire_str+="/*.png"
    x=glob.glob(repertoire_str)

    commande = "./prog "+filepath +" 1"
    os.system(commande)
    filename1 = PhotoImage(file = filepath)
    img1 = canvas.create_image(400, 350, image=filename1)
    canvas.pack(expand="yes", fill = "both",padx=10, pady=10)

    commande="g++-5 fonctions.cpp -o fonctions"
    os.system(commande)
    tmp=False

    pb = ttk.Progressbar(canvas, orient="horizontal", length=200,mode="determinate")
    pb.pack(side=RIGHT)
    compteur=1
    longueur=len(x)
    max=0
    empreinte_finale=""
    for i in x:
        pb.step(100/longueur)

        window.update()
        compteur+=1

        commande = "./prog "+i +" 2"
        os.system(commande)
        commande="./fonctions"
        os.system(commande)

        fichier = open("resultat.txt", "r")
        lignes=fichier.read()
        lignes=int(lignes)
        if (lignes>max):
            empreinte_finale=i
            max=lignes

    if (max>=min_legal):
        pb.pack_forget()
        tmp=True
        filename2 = PhotoImage(file = empreinte_finale)
        img2 = canvas.create_image(1500, 350, image=filename2)
        canvas.pack(expand="yes", fill = "both",padx=10, pady=10)

        text1=canvas.create_text(950,600,text="Match : "+"100%",fill="red",font=("Geneva",21))
    if ((max<min_legal)and(max>7)):
        pb.pack_forget()
        tmp=True
        filename2 = PhotoImage(file = empreinte_finale)
        img2 = canvas.create_image(1500, 350, image=filename2)
        canvas.pack(expand="yes", fill = "both",padx=10, pady=10)

        text1=canvas.create_text(950,600,text="Match : "+str((max*100)/min_legal)+"%",fill="red",font=("Geneva",21))
    if (max<=7):
        pb.pack_forget()
        text1=canvas.create_text(1500,400,text="Aucune empreinte ne correspond",fill="red",font=("Geneva",21))

    fichier.close()
    os.system("rm ratio1.txt ratio2.txt")
    os.system("rm resultat.txt")
    window.mainloop()


def afficher_empreinte_option3(premier,deuxieme):
    popo=Toplevel()
    img1 = ImageTk.PhotoImage(Image.open(premier))
    panel1 = Label(popo, image = img1,width=300, height=300)
    panel1.pack(side = "left",expand="yes", fill = "both",padx=10, pady=10)
    img2 = ImageTk.PhotoImage(Image.open(deuxieme))
    panel2 = Label(popo, image = img2,width=300, height=300)
    panel2.pack(side = "right",expand="yes", fill = "both",padx=10, pady=10)

    popo.title("Details du processus")
    popo.geometry("1920x1920")
    popo.configure(background='grey')
    popo.mainloop()



def retrouver_empreinte():#regroupes les empreinets identiques (mode 3)
    canvas.delete("all")
    window.title("Retrouver les empreintes d'une même personne dans un repertoire")

    repertoire_str=tkFileDialog.askdirectory(title="Choisir un repertoire")
    dd=repertoire_str

    repertoire_str+="/*.png"
    x=glob.glob(repertoire_str)
    commande="g++-5 fonctions.cpp -o fonctions"
    os.system(commande)
    pb = ttk.Progressbar(window, orient="horizontal", length=200,mode="determinate")
    pb.pack()
    longueur=len(x)
    compteur=0
    toto=100/(longueur+1)
    liste_finale=[]
    place=10
    temps_estime=13.7*longueur/60
    temps_estime=Decimal(str(round(temps_estime,2)))


    text1=canvas.create_text(500,300,text="Le processus peut prendre un peu de temps",fill="red",font=("Geneva",22))
    text2=canvas.create_text(1500,300,text="Temps estimé :"+str(temps_estime)+" min",fill="red",font=("Geneva",22))

    for i in range(longueur):
        liste_tmp=[]
        liste_tmp.append(x[i])
        place+=50
        compteur=0
        compteur2=0
        pb.step(toto)

        window.update()
        commande = "./prog "+x[i] +" 1"
        os.system(commande)
        img=ImageTk.PhotoImage(Image.open(x[i]))
        for j in range(longueur):

            commande = "./prog "+x[j] +" 2"
            os.system(commande)
            commande="./fonctions"
            os.system(commande)

            fichier = open("resultat.txt", "r")
            lignes=fichier.read()

            if ((int(lignes)>=min_legal)and(i!=j)):
                compteur+=1
                liste_tmp.append(x[j])
                compteur2+=1

            if (j==len(x)-1):
                liste_finale.append(liste_tmp)
                #pb.stop()
                #window.update()

                os.system("rm ratio2.txt")
                os.system("rm resultat.txt")

    pb.stop()
    text3=canvas.create_text(1500,300,text="Terminé",fill="red",font=("Geneva",22))

    compteur=0
    os.system("mkdir "+dd+"/Orphelins")
    for i in range(len(liste_finale)):
        if len(liste_finale[i])==1:
            tmp=liste_finale[i]
            os.system("cp "+tmp[0]+" "+dd+"/Orphelins")
            liste_finale[i].append("end")


    for i in liste_finale:
        if i[len(i)-1]!="end":
            compteur+=1
            os.system("mkdir "+dd+"/"+str(compteur))
            for j in i:
                os.system("cp "+j+" "+dd+"/"+str(compteur)+"/")

    try:
        adresse_orphelin=dd+"/Orphelins/*.png"
        x=len(glob.glob(adresse_orphelin))
    except:
        x=0

    canvas.delete("all")
    text1=canvas.create_text(500,300,text=str(compteur)+" Dossier(s)",fill="red",font=("Geneva",22))
    text2=canvas.create_text(1500,300,text=str(x)+" Empreintes Orphelines",fill="red",font=("Geneva",22))


def perso():#permet de choisir le filtre a appliquer (mode 4)
    canvas.delete("all")
    commande="g++-5 -std=c++1y -o filtre_generique -Wall -Wextra -Weffc++ -pedantic -Wl,-rpath,. filtre_generique.cpp libeistipng.so"
    os.system(commande)
    window.title("Personnaliser le processus")

    filepath1 = tkFileDialog.askopenfilename(title="Choisir la première image",filetypes=[('png files','.png'),('all files','.*')])
    filepath2 = tkFileDialog.askopenfilename(title="Choisir la deuxième image",filetypes=[('png files','.png'),('all files','.*')])

    global v
    v = IntVar()
    v.set(0)  # initializing the choice, i.e. Python

    languages = [("Filtre median",1),("Filtre moyenneur",2),("Sans filtre",3)]

    global label_frame,tmp
    label_frame = LabelFrame(canvas, text="Choisir le filtre")
    for txt, val in languages:
        tmp=Radiobutton(label_frame,text=txt,padx = 20,variable=v,command=lambda : ShowChoice(filepath1,filepath2),value=val)
        tmp.pack(anchor=CENTER)

    canvas.create_window(900, 50, window=label_frame)
    window.mainloop()



def ShowChoice(filepath1,filepath2):#(mode 4 suite)
    a= v.get()
    global img1,panel1
    canvas.delete("all")

    if (a==1):
        commande="./filtre_generique "+filepath1+" 1 1"
        os.system(commande)

        filename1 = PhotoImage(file = "filtre_median1.png")
        img1 = canvas.create_image(400, 350, image=filename1)
        canvas.pack(expand="yes", fill = "both",padx=10, pady=10)

    if (a==2):
        commande="./filtre_generique "+filepath1+" 1 2"
        os.system(commande)

        filename1 = PhotoImage(file = "filtre1.png")
        img1 = canvas.create_image(400, 350, image=filename1)
        canvas.pack(expand="yes", fill = "both",padx=10, pady=10)

    if (a==3):
        commande="./filtre_generique "+filepath1+" 1 3"
        os.system(commande)

        filename1 = PhotoImage(file = "binarise1.png")
        img1 = canvas.create_image(400, 350, image=filename1)
        canvas.pack(expand="yes", fill = "both",padx=10, pady=10)

    window.update()

    global c
    c = IntVar()
    c.set(0)  # initializing the choice, i.e. Python

    languages = [("Filtre median",1),("Filtre moyenneur",2),("Sans Filtre",3)]

    global label2
    label2=Label(canvas,text="Choisissez le filtre:",justify = LEFT,padx = 20)
    label2.pack()

    for txt, val in languages:
        tmp=Radiobutton(canvas,text=txt,padx = 20,variable=c,command=lambda : ShowChoice2(filepath2),value=val)
        tmp.pack(anchor=CENTER)
    canvas.delete(label2)
    window.mainloop()

def squelette3():#affiche le squelette des deux empreintes pour le mode 4
    popo=Toplevel()
    img1 = ImageTk.PhotoImage(Image.open("bifurcation1.png"))
    img2 = ImageTk.PhotoImage(Image.open("bifurcation2.png"))
    panel1 = Label(popo, image = img1,width=300, height=300)
    panel2 = Label(popo, image = img2,width=300, height=300)
    panel1.pack(side = "left",expand="yes", fill = "both",padx=10, pady=10)
    panel2.pack(side = "right",expand="yes", fill = "both",padx=10, pady=10)

    popo.title("Details du processus")
    popo.geometry("1920x1920")
    popo.configure(background='grey')
    popo.mainloop()


def ShowChoice2(filepath1):#suite mode 4
    a= c.get()
    if (a==1):
        commande="./filtre_generique "+filepath1+" 2 1"
        os.system(commande)
        filename2 = PhotoImage(file = "filtre_median2.png")
        img2 = canvas.create_image(1500, 350, image=filename2)
        canvas.pack(expand="yes", fill = "both",padx=10, pady=10)

        label2.forget()
    if (a==2):
        commande="./filtre_generique "+filepath1+" 2 2"
        os.system(commande)
        filename2 = PhotoImage(file = "filtre2.png")
        img2 = canvas.create_image(1500, 350, image=filename2)
        canvas.pack(expand="yes", fill = "both",padx=10, pady=10)
    if (a==3):
        commande="./filtre_generique "+filepath1+" 2 3"
        os.system(commande)

        filename1 = PhotoImage(file = "binarise2.png")
        img1 = canvas.create_image(1500, 350, image=filename1)
        canvas.pack(expand="yes", fill = "both",padx=10, pady=10)

        label2.forget()

    window.update()
    commande="g++-5 fonctions.cpp -o fonctions"
    os.system(commande)
    commande="./fonctions"
    os.system(commande)


    fichier = open("resultat.txt", "r")
    lignes=fichier.read()
    fichier.close()
    #os.system("rm ratio1.txt ratio2.txt")
    #os.system("rm resultat.txt")

    global match
    tmp=int(lignes)
    if (tmp>=min_legal):
        text1=canvas.create_text(950,600,text="Match : "+"100%",fill="red",font=("Geneva",21))
    if ((tmp>7)and(tmp<min_legal)):
        text1=canvas.create_text(950,600,text="Match : "+str((tmp*100)/min_legal)+"%",fill="red",font=("Geneva",21))
    if(tmp<=7):
        text1=canvas.create_text(950,600,text="No Match : "+str((tmp*100)/min_legal)+"%",fill="red",font=("Geneva",21))


    button1 = Button(canvas,text="Afficher la squelettisation",command=squelette3,bd=5)
    button1.configure()
    button1_window = canvas.create_window(950, 90, anchor=N, window=button1)

    window.mainloop()


def traiter_image():#permet de traiter une image (mode 5)
    canvas.delete("all")
    window.title("Traitement d'image")
    global filepath
    filepath = tkFileDialog.askopenfilename(title="Ouvrir une image",filetypes=[('png files','.png'),('all files','.*')])
    filename1 = PhotoImage(file = filepath)
    img1 = canvas.create_image(950, 350, image=filename1)
    canvas.pack(expand="yes", fill = "both",padx=10, pady=10)

    button1 = Button(canvas,text="Egalisation d'histogramme",command=lambda : appliquer_traitement(1,filepath),bd=5, anchor = W)
    button1.configure()
    button1_window = canvas.create_window(1500, 10, anchor=N, window=button1)
    button2 = Button(canvas,text="Inverser couleur",command=lambda : appliquer_traitement(2,filepath),bd=5, anchor = W)
    button2.configure()
    button2_window = canvas.create_window(1500, 60, anchor=N, window=button2)
    button3 = Button(canvas,text="Filtre Passe-Haut",command=lambda : appliquer_traitement(3,filepath),bd=5, anchor = W)
    button3.configure()
    button3_window = canvas.create_window(1500, 110, anchor=N, window=button3)
    button4 = Button(canvas,text="Inverser sens de l'image",command=lambda : appliquer_traitement(4,filepath),bd=5, anchor = W)
    button4.configure()
    button4_window = canvas.create_window(1500, 160, anchor=N, window=button4)
    button6 = Button(canvas,text="Filtre Median",command=lambda : appliquer_traitement(6,filepath),bd=5, anchor = W)
    button6.configure()
    button6_window = canvas.create_window(1500, 260, anchor=N, window=button6)
    button7 = Button(canvas,text="Filtre Moyenneur",command=lambda : appliquer_traitement(7,filepath),bd=5, anchor = W)
    button7.configure()
    button7_window = canvas.create_window(1500, 310, anchor=N, window=button7)

    window.mainloop()

def appliquer_traitement(choix,filepath):#(suite mode 5)
    commande="g++-5 -std=c++1y -o traitement_seul -Wall -Wextra -Weffc++ -pedantic -Wl,-rpath,. traitement_seul.cpp libeistipng.so"
    os.system(commande)
    if choix==1:
        commande="./traitement_seul "+filepath+" 1"
        os.system(commande)
        filename1 = PhotoImage(file = "traitement.png")
        img1 = canvas.create_image(950, 350, image=filename1)
        canvas.pack(expand="yes", fill = "both",padx=10, pady=10)
    if choix==2:
        commande="./traitement_seul "+filepath+" 2"
        os.system(commande)
        filename1 = PhotoImage(file = "traitement.png")
        img1 = canvas.create_image(950, 350, image=filename1)
        canvas.pack(expand="yes", fill = "both",padx=10, pady=10)
    if choix==3:
        commande="./traitement_seul "+filepath+" 3"
        os.system(commande)
        filename1 = PhotoImage(file = "traitement.png")
        img1 = canvas.create_image(950, 350, image=filename1)
        canvas.pack(expand="yes", fill = "both",padx=10, pady=10)
    if choix==4:
        commande="./traitement_seul "+filepath+" 4"
        os.system(commande)
        filename1 = PhotoImage(file = "traitement.png")
        img1 = canvas.create_image(950, 350, image=filename1)
        canvas.pack(expand="yes", fill = "both",padx=10, pady=10)
    if choix==6:
        commande="./traitement_seul "+filepath+" 6"
        os.system(commande)
        filename1 = PhotoImage(file = "traitement.png")
        img1 = canvas.create_image(950, 350, image=filename1)
        canvas.pack(expand="yes", fill = "both",padx=10, pady=10)
    if choix==7:
        commande="./traitement_seul "+filepath+" 7"
        os.system(commande)
        filename1 = PhotoImage(file = "traitement.png")
        img1 = canvas.create_image(950, 350, image=filename1)
        canvas.pack(expand="yes", fill = "both",padx=10, pady=10)
    window.mainloop()





def about():#informations sur les auteurs
    about=Toplevel()
    about.title("Auteurs")

    texte="Version Alpha\r Distributeurs : Laverdine Clément, Piotrowski Bastien, Vincent Victor, Caucheteux Léo-Paul, Beauplet Gabriel"
    label = Label(about, text=texte)
    label.pack()

    img1 = ImageTk.PhotoImage(Image.open('photo_groupe.png').resize((400,300)))
    panel1 = Label(about, image = img1,width=300, height=300)
    panel1.pack(expand="yes", fill = "both",padx=10, pady=10)

    about.mainloop()

def about2():#aide de l'utilisateur
    about=Tk()
    about.title("Aide")
    texte1="Comparer des empreintes"
    label = Label(about, text=texte1,font='bold').pack()
    texte2="Ce mode vous permet de trouver la ressemblance entre deux empreintes\r1-Choisissez deux empreintes à comparer\r2-Attendez que le processus se termine\r"
    label = Label(about, text=texte2).pack()
    texte1="Comparer une empreinte avec un repertoire"
    label = Label(about, text=texte1,font='bold').pack()
    texte2="A partir d'une empreinte référence, ce mode vous permet de trouver au sein d'un repertoire, une empreinte similaire\r1-Choisissez l'empreinte référence\r2-Choisissez le répertoire à fouiller\r"
    label = Label(about, text=texte2).pack()
    texte1="Retrouver les empreintes d'une même personne dans un repertoire"
    label = Label(about, text=texte1,font='bold').pack()
    texte2="Ce mode vous permet de trouver toutes les empreintes identiques dans un repertoire\r1-Choisissez le repertoire\r2-Attendez que le processus se termine\r3-Les empreintes similaires sont regroupées par dossier et les empreintes n'ayant pas de 'match' sont dans un dossier nommé 'Orphelines'\r"
    label = Label(about, text=texte2).pack()
    texte1="Personnaliser le processus"
    label = Label(about, text=texte1,font='bold').pack()
    texte2="Ce mode vous permet de comparer deux empreintes en choisissant le filtre que vous souhaitez appliquer pour chaque empreinte\r1-Choisissez les deux empreintes\r2-Choisissez le filtre pour chaque empreinte\r"
    label = Label(about, text=texte2).pack()
    texte1="Traiter image"
    label = Label(about, text=texte1,font='bold').pack()
    texte2="Ce mode vous permet de modifier l'image\r1-Choisissez l'image à traiter\r2-L'image qui apparait est l'image traitée\r3-Vous pouvez la retrouver dans le repertoire courant sous 'traitement.png' "
    label = Label(about, text=texte2).pack()





def choix():#bouton du menu principal
    bouton1=Button(window, text="Comparer deux empreintes",command=tout,bd=5)
    bouton2=Button(window, text="Comparer une empreinte avec un repertoire",command=repertoire,bd=5)
    bouton3=Button(window, text="Retrouver les empreintes d'une même personne dans un repertoire",command=retrouver_empreinte,bd=5)
    bouton4=Button(window, text="Personnaliser le processus",command=perso,bd=5)
    bouton5=Button(window, text="Traiter image",command=traiter_image,bd=5)
    bouton1.pack(side=TOP)
    bouton2.pack(side=TOP)
    bouton3.pack(side=TOP)
    bouton4.pack(side=TOP)
    bouton5.pack(side=TOP)
    window.mainloop()


menubar = Menu(window)
commande="rm resultat.txt"
menu1=Menu(menubar)
menu1.add_command(label="Exit",command=window.quit)

menu2=Menu(menubar)
menu2.add_command(label="Aide",command=about2)
menu2.add_command(label="Auteurs",command=about)
menu2.add_command(label="Changer minimum de minuties",command=changer_min_legal)


menubar.add_cascade(label="File",menu=menu1)
menubar.add_cascade(label="A Propos",menu=menu2)
window.config(menu = menubar)


window.title("Fingerprints")
window.geometry("1920x1920")
window.configure(background='grey')

choix()
