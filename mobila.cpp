/*
    INVENTARUL UNUI MAGAZIN DE MOBILA
    Programul manipuleaza datele din inventarul unui magazin de mobila.

    Datele de intrare din fisier sunt memorate in urmatoarea ordine: 
    Numarul total de mobila din inventar (total_mob)
    <clasa Mobila>
    Numele mobilierului (tip)
    Numarul de piese care trebuie asamblate (comp.nr_piese)
    Piesele principale (comp.comp_princip)
    Stocul actual (stoc)
    Pretul (pret)
    <clasa Vanzari>
    Tipul de mobilier (mobila)
    Numarul de vanzi (nr_vnz)

    Asupra datelor, se pot face urmatoarele operatii: 
        - afisarea informatiilor memorate in clase
        - afisarea datelor membre ale claselor
        - afisearea numarul total de adaugari in inventar
        - adaugarea in inventar a unui tip nou de mobilier
        - actualizarea stocului, pretului, nr. de vanzari
        - stergerea din inventar
        - calcularea venitului total din vanzari

    In cazul in care stocul este scazut, programul va genera o sugestie de crestere a pretului cu 5%
    (apelarea functiei private stoc_redus)

*/

#include<iostream>
#include<cstring>

class Vanzari{
    
    char* mobila;
    int nr_vnz;
    
    public:

    //constructor de initializare
    Vanzari(const char* m="", int nr_vnz=0): nr_vnz{nr_vnz}{
        mobila = new char[strlen(m)+1];
        strcpy(mobila,m);
    }

    void setMobila(const char* m){
        delete [] mobila;
        mobila= new char[strlen(m)+1];
        strcpy(mobila,m);
    }

    void setNrVanzari(int nr_vnz){
        this->nr_vnz=nr_vnz;
    }
    
    int getNrCl() const {return nr_vnz;} 
    char* getTip() const {return mobila;}
    
    //constructor de copiere
    Vanzari(const Vanzari & vanz) : nr_vnz{vanz.nr_vnz}{
        mobila=new char[strlen(vanz.mobila)+1];
        strcpy(mobila,vanz.mobila);
    } 

    //supraincarcarea operatorului "="
    Vanzari & operator=(const Vanzari& vanz){
        if(this!=&vanz){
        delete [] mobila;
        mobila=new char[strlen(vanz.mobila)+1];
        strcpy(mobila,vanz.mobila);
        nr_vnz=vanz.nr_vnz;
    }
    return *this;
}

    //Destructor
    ~Vanzari(){delete [] mobila;}
    
    //supraincarcarea operatorului ">>"
    friend std::istream& operator >>(std::istream & in, Vanzari &vanz){
        int nrc;
        delete [] vanz.mobila; // linie de cod necesara pentru a trata cazul in care variabila avea deja memorie alocata
        vanz.mobila=new char[100]; 
        in.ignore();
        in.getline(vanz.mobila,100); 
        in>>nrc;
        in.ignore();
        vanz.nr_vnz=nrc;
        return in;
    }

//supraincarcarea operatorului "<<"
friend std::ostream & operator<<(std::ostream & out,const Vanzari& vanz){
    
    out<<"< Vanzari >"<<'\n';
    out<<vanz.mobila<<" ---> "<<vanz.nr_vnz<<'\n';
    return out;
}

//supraincarcarea operatorului "+"

    // Obiect de tip Vanzari + nr_vanzari
     Vanzari & operator+(int vanz){
        nr_vnz+=vanz;
        return *this;
    }

      //  nr_vanzari + Obiect de tip Vanzari 
    friend Vanzari & operator+(int vanz, Vanzari& v){
        v.nr_vnz+=vanz;
        return v;
    }

};

class Componente{
    unsigned int nr_piese;
    char* comp_princip;
    
    public:
    //constructorul de initializare
    Componente(unsigned int nr_piese=0, const char* comp_pr="") : nr_piese{nr_piese} {
        comp_princip=new char[strlen(comp_pr)+1]; 
        strcpy(comp_princip, comp_pr);
    };

    //constructorul de copiere
    Componente(const Componente &comp): nr_piese{comp.nr_piese} {
        comp_princip=new char[strlen(comp.comp_princip)+1];
        strcpy(comp_princip, comp.comp_princip);
    }
    
    void setNr_piese(unsigned int nr){
        nr_piese=nr;
    }

    void setComp(const char* comp){
        strcpy(comp_princip,comp);
    }
    
    int getNr_piese() const{ return nr_piese; };
    char* getComp() const {return comp_princip; };
    
    //supraincarcarea operatorului <<
   friend std::ostream& operator<<(std::ostream &out, const Componente & comp){
        out<<"\nComponentele principale sunt: "<<comp.comp_princip<<"\n\n";
        return out;
    }
    //supraincarcarea operatorului >>
    friend std::istream& operator>>(std::istream& in, Componente& comp){

        std::cout<<" Numarul de componente: "; in>>comp.nr_piese;
        std::cout<<" Componentele principale: "; 
        in.ignore();
        in.getline(comp.comp_princip,100);
        return in;
    }
    //supraincarcarea operatorului =
    Componente & operator=(const Componente & comp){
        nr_piese=comp.nr_piese;
        strcpy(comp_princip,comp.comp_princip);
        return *this;
    }
    ~Componente(){delete [] comp_princip;}

};

class Mobila{
    char tip[50];
    Componente comp;
    int stoc, pret; 
    static int nr_actualizari;

    inline void stoc_redus(){
        int op;
        bool loop=true;
        while(loop){
            std::cout<<"\n Stocul este redus - doriti sa mariti pretul cu 5%? \n Tastati\n  1 -> aplicarea scumpirii\n  2 -> nemodificarea pretului\n";
            std::cin>>op;
          //  std::cin.ignore();
            if(op!=1 && op!=2)
                std::cout<<"\n Input invalid!\n";
            else{
                if(op==1){
                    setPret(pret*1.05);
                }
                loop=false;
            }
        }
    }
    
    public:
    //constructorul de initializare
    Mobila(const char tip_[]="", const Componente& comp_={0,""}, int stoc_=0, int pret_=0):
    comp{comp_}, stoc{stoc_}, pret{pret_} {strcpy(tip,tip_);}
    
    //supraincarcarea operatorului >>
    friend std::istream& operator>>(std::istream &in, Mobila& mob ){
        char linie[100];
        int x;
        in.getline(linie,100);
        strcpy(mob.tip,linie);
        in>>x;
        in.ignore();
        in.getline(linie,100);
        mob.comp.setComp(linie);
        mob.comp.setNr_piese(x);

        in>>x;
        in.ignore();
        mob.stoc=x; 
        in>>x;
        in.ignore();
        mob.pret=x;       
    return in;
    }
    //supraincarcarea operatorului <<
   friend std::ostream& operator<<(std::ostream & out, const Mobila& mob){ 
        
        out<<'\n'<<mob.tip<<'\n';
        out<<"Stocul disponibil: "<<mob.stoc<<'\n';
        out<<"Pretul: "<<mob.pret<<"\n";
        out<<"Numarul de componente: "<<mob.comp.getNr_piese()<<"\n";
        out<<"Componente principale: "<<mob.comp.getComp()<<"\n\n";
    
    return out;
    }

    const char* getTip() const{return tip;}

    void afisComp() const{ std::cout<<comp; }
    void setComp(){std::cin>>comp;}
    void setTip(const char* tip_){
        strcpy(tip,tip_);
    }
    void setStoc(int stoc_){
        stoc=stoc_;
        if(stoc_<5)
            stoc_redus();
    }
    void setPret(int pret_){
        pret=pret_;
    }
    int getNrAct () const {return nr_actualizari;}
    void setNrAct() {nr_actualizari++;}

    //constructorul de copiere
    Mobila(const Mobila& mob) : comp{mob.comp}, stoc{mob.stoc}, pret{mob.pret} {strcpy(tip,mob.tip);}

    //supraincarcarea operatorului =
    Mobila & operator=(const Mobila & mob){

        strcpy(tip,mob.tip);
        stoc=mob.stoc;
        pret=mob.pret;
        comp=mob.comp;
        return *this;
    }
    ~Mobila(){}
    
    inline int venit(const Vanzari& vanz){
        return pret*vanz.getNrCl();
    }
};

int Mobila::nr_actualizari=0;

int main(){

    Mobila mobila[100]{ {"canapea",{3,"cadrul, elemente de cuplare, chingi elastice"},10,800}, 
    {"dulap",{3,"usi, cutii de depozitare, balamale"}, 20,1500},{"pat",{3,"cadru, sertare, saltea"},12,1700}};
    Vanzari vanz[100]{{"canapea", 11},{"dulap",20},{"pat",21}};

    int total_mob=3,i,x,optiune;
    char input[100],ok;
    bool loop=true;

    while(loop){

        std::cout <<
    "--------------------------------------------------          __________.\n"
    "|                    MENIU                       |         /_/-----/_/|   __\n"
    "--------------------------------------------------         ( ( ' ' ( (| /'--'\\\n"
    "| 1  - Afisare detalii despre mobila             |         (_( ' ' (_(|/_    _\\\n"
    "| 2  - Afisati componentele principale           |         / /=====/ /|  '||'\n"
    "| 3  - Afiseaza numarul de vanzari               |        /_//____/_/ |   ||\n"
    "| 4  - Adaugati mobilier                         |       (o|:.....|o) |   ||\n"
    "| 5  - Actualizati stocul mobilierului           |       |_|:_____|_|/'  _||_\n"
    "| 6  - Actualizati pretul mobilierului           |        '         '   /____\\\n"
    "| 7  - Actualizati nr. vanzari al mobilierului   |\n"
    "| 8  - Stergeti mobilier din inventar            |\n"
    "| 9  - Calculeaza venitul din vanzari            |\n"
    "| 10 - Afisati numarul de obiecte recent adaugate|\n"
    "| 11 - Iesire                                    |\n"
    "--------------------------------------------------\n"
    "Alegeti optiunea: ";
  

    std::cin.getline(input,100);
    //tratarea cazului in care se citeste de la tastatura un caracter in loc de un numar
    try {
        optiune = std::stoi(input);
    } catch (...) {
        std::cout << "\n Introduceti un numar intre 1 si 10 \n";
        continue;
    }

    switch(optiune){

        //Afisare detalii despre mobila 
        case 1:
        std::cout<<" Tastati\n 1--> Afisati informatii despre TOT mobilierul \n 2--> Tastati numele piesei de mobilier \n";
        std::cin>>optiune;
        std::cin.ignore();
        if(optiune==1)
            for(i=0;i<total_mob;++i)
                std::cout<<mobila[i]<<vanz[i];
        else if(optiune==2){
            ok=1;
           // std::cin.ignore();
            std::cin.getline(input,100);
            for(i=0;i<total_mob;++i){
                if(input==mobila[i].getTip()){
                    std::cout<<mobila[i];
                    ok=0;
                    break;
                }      
            }
        if(ok==1)
            std::cout<<"Input invalid - "<<input<<" nu exista in inventar\n";
        }
        else
        std::cout<<"\n Optiune invalida!";
    break;
    
    case 2:
    //Afisati componentele principale
        std::cout<<" Tastati numele piesei de mobilier \n";
        std::cin.getline(input,100);
        ok=0;
        for(i=0;i<total_mob;++i){
            if(input==mobila[i].getTip()){
                mobila[i].afisComp();
                ok=1;
        }
    }
        if(ok==0)
            std::cout<<"\nInput invalid - "<<input<<" nu exista in inventar\n";       
    break;
    
    //Afiseaza numarul de vanzari 
    case 3:
        std::cout<<" Tastati\n 1--> Afiseaza numarul total de vanzari \n 2--> Afiseaza numarul de vanzari inregistrati pentru o piesa de mobilier \n";
        std::cin>>optiune;
        std::cin.ignore();

        if(optiune==1){
            unsigned int cnt=0;
            for(i=0;i<total_mob;++i)
                cnt+=vanz[i].getNrCl();
            std::cout<<"Numar total de vanzari : "<<cnt<<'\n';
        }
        else if(optiune==2){
            ok=1;

            std::cin.getline(input,100);
            for(i=0;i<total_mob;++i){
                if(input==vanz[i].getTip()){
                    std::cout<<vanz[i];
                    ok=0;
                    break;
                }      
            }
        if(ok==1)
            std::cout<<"Input invalid - "<<input<<" nu exista in inventar\n";
        }
        else
        std::cout<<"\n Optiune invalida\n"; 
    break;        
    
    //Adaugati mobilier
    case 4:
    if(total_mob>=100){
        std::cout<<"\nNu mai este loc in depozit pentru un tip nou de mobila!\n";
    }
    else{
        std::cout<<"\n Tipul mobilierului : "; 
        //std::cin.ignore();
        std::cin.getline(input,100);
        mobila[total_mob].setTip(input);
        vanz[total_mob].setMobila(input);
        std::cout<<" Pretul: "; std::cin>>x;
        mobila[total_mob].setPret(x);
        std::cout<<" Stocul: "; 
        std::cin>>x;
        std::cin.ignore();
        mobila[total_mob].setStoc(x);
        mobila[total_mob].setComp();

        std::cout<<" Numarul de vanzari: "; std::cin>>x;
        vanz[total_mob].setNrVanzari(x);
        total_mob++;
        mobila[0].setNrAct();
        //std::cin.ignore();
    }
    break;

    //Actualizati stocul mobilierului    
    case 5:
        ok=1;
        std::cout<<"\n Tipul mobilierului: ";
        //std::cin.ignore();
        std::cin.getline(input,100);

            for(i=0;i<total_mob;++i){
                if(input==mobila[i].getTip()){
                    std::cout<<"\n Stocul actualizat: ";
                    std::cin>>x;
                    std::cin.ignore();
                    mobila[i].setStoc(x);

                    ok=0;
                    break;
                }      
            }
        if(ok==1)
            std::cout<<"Input invalid - "<<input<<" nu exista in inventar\n";
        
    break;

   // Actualizati pretul mobilierului   
    case 6:
        ok=1;
        std::cout<<"\n Tipul mobilierului: ";
        //std::cin.ignore();
        std::cin.getline(input,100);
            for(i=0;i<total_mob;++i){
                if(input==mobila[i].getTip()){
                    std::cout<<" Pretul actualizat: ";
                    std::cin>>x;
                    std::cin.ignore();
                    mobila[i].setPret(x);
                    ok=0;
                    break;
                }      
            }
        if(ok==1)
            std::cout<<"Input invalid - "<<input<<" nu exista in inventar\n";
        break;

        //Actualizati nr. vanzari al mobilierului
        case 7:
        ok=1;
        std::cout<<"\n Tipul mobilierului: ";
        //std::cin.ignore();
        std::cin.getline(input,100);
            for(i=0;i<total_mob;++i){
                if(strcmp(input,vanz[i].getTip())==0){
                    
                    std::cout<<"\n Tastati\n 1 --> Setati numarul de vanzari\n 2 --> Adaugati un numar de vanzari la cel actual\n ";
                    std::cin>>x;
                    if(x==1){
                        std::cout<<" Numar vanzari: ";
                        std::cin>>x;
                        std::cin.ignore();
                        vanz[i].setNrVanzari(x); 
                        ok=0;
                        break;

                    }
                    else if(x==2){
                    std::cout<<"\n Introduceti numarul de vanzari care vor fi inregistrate\n";
                    std::cin>>x;
                    vanz[i]=vanz[i]+x; // se foloseste supraincarcarea operatorului "+"
                    ok=0;
                    break;
                    }
                }      
            }
        if(ok==1)
            std::cout<<"Input invalid - "<<input<<" nu exista in inventar\n";
    break;

    //Stergeti mobilier din inventar
    case 8:
        ok=1;
        std::cout<<"\n Tipul mobilierului: ";
        //std::cin.ignore();
        std::cin.getline(input,100);
            for(i=0;i<total_mob;++i){
                if(input==mobila[i].getTip()){
                    for(int j=i;j<total_mob-1;--j)
                        mobila[j]=mobila[j+1];
                    ok=0;
                    total_mob--;
                    std::cout<<"\nInventarul a fost actualizat!\n";
                }      
            }
        if(ok==1)
            std::cout<<"Input invalid - "<<input<<" nu exista in inventar\n";
    break;
    
    //Calculeaza venitul din vanzari   
    case 9:
    std::cout<<" Tastati\n 1--> Afisati venitul total \n 2--> Afisare venitul total din vanzari unei singure piese de mobilier \n";
        std::cin>>optiune;
        std::cin.ignore();
        x=0;
        if(optiune==1){
            for(i=0;i<total_mob;i++)
                x+=mobila[i].venit(vanz[i]);
            std::cout<<"\n Venit total din vanzari: "<<x<<'\n';
        }
        else if(optiune==2){
            ok=1;
            std::cout<<"Mobila : ";
            //std::cin.ignore();
            std::cin.getline(input,'\n');
            for(i=0;i<total_mob;++i){
                if(input==mobila[i].getTip()){
                    x=mobila[i].venit(vanz[i]);
                    std::cout<<"Venitul total din vanzarile de "<<input<<" este de "<<x<<" ron"<<'\n';
                    ok=0;
                    break;
                }      
            }
        if(ok==1)
            std::cout<<"Input invalid - "<<input<<" nu exista in inventar\n";
        }
        else
        std::cout<<"\n Optiune invalida!";       
    break;

    //Afisati numarul de obiecte recent adaugate
    case 10:
    std::cout<<"Numarul pieselor de mobilier recent adaugate: \n";   
    std::cout<<mobila[0].getNrAct()<<'\n';
    break; 

    //Iesire
    case 11:{
    loop=false;
    break;
}

    default:
    std::cout<<"\nTastati un numar intre 1 si 10\n";
    break;
}
}

return 0;

}


