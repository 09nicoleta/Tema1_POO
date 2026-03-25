/*
    Programul manipuleaza datele despre inventarul si clientii unui magazin de mobila.

    Datele de intrare din fisier sunt memorate in urmatoarea ordine: 
    Numarul total de mobila din inventar (total_mob)
    <clasa Mobila>
    Numele mobilierului (tip)
    Numarul de piese care trebuie asamblate (comp.nr_piese)
    Piesele principale (comp.comp_princip)
    Stocul actual (stoc)
    Pretul (pret)
    <clasa Clienti>
    Tipul de mobilier (mobila)
    Numarul de clienti (nr_cl)

    Asupra datelor, se pot face urmatoarele operatii: 
        - afisarea informatiilor memorate in clase
        - afisarea datelor membre ale claselor
        - afiseaza numarul total de adaugari in inventar
        - adaugarea in inventar a unui tip nou de mobilier
        - actualizarea stocului, pretului, nr. de clienti
        - stergerea din inventar
        - calcularea venitului total din vanzari

    In cazul in care stocul este scazut, programul va genera o sugestie de crestere a pretului cu 5%
    (apelarea functiei private stoc_redus)

    Optiunea "11 - Iesire" salveaza actualizarile facute prin suprascrierea fisierului de intrare
*/

#include<iostream>
#include<string>
#include<fstream>

class Clienti{
    
    std::string mobila;
    int nr_cl;
    
    public:
    Clienti(const std::string& mob="", int nr_cl=0):
    mobila(mob), nr_cl{nr_cl} {};

    inline void setMobila(const std::string& mobila){
        this->mobila=mobila;
    }

    inline void setNrClienti(int nr_cl){
        this->nr_cl=nr_cl;
    }
    
    int getNrCl() const {return nr_cl;} 
    std::string getTip() const {return mobila;}
    
    Clienti(const Clienti & cli): mobila{cli.mobila}, nr_cl{cli.nr_cl} {}

    Clienti & operator=(const Clienti& cli){
        mobila=cli.mobila;
        nr_cl=cli.nr_cl;
        return *this;
    }
    ~Clienti(){}

    friend std::istream& operator >>(std::istream & in, Clienti &client){
        std::string tip;
        int nrc;
        std::getline(in,tip);
        client.mobila=tip;
        in>>nrc;
        in.ignore();
        client.nr_cl=nrc;
        return in;
    }

friend std::ostream & operator<<(std::ostream & out,const Clienti& cli){
    
    std::cout<<"< Clienti >"<<'\n';
    std::cout<<cli.mobila<<" ---> "<<cli.nr_cl<<'\n';
    return out;
}

    void scrieFisier(std::ostream &out) const{
        out<<mobila<<'\n';
        out<<nr_cl<<'\n';
    }
};

class Componente{
    unsigned int nr_piese;
    std::string comp_princip;

    
    public:
    Componente(unsigned int nr_piese=0, const std::string& comp_pr="") : 
    nr_piese{nr_piese}, comp_princip(comp_pr) {};

    Componente(const Componente &comp): nr_piese{comp.nr_piese}, comp_princip{comp.comp_princip} {}
    
    inline void setNr_piese(unsigned int nr){
        nr_piese=nr;
    }

    inline void setComp(const std::string& comp){
        comp_princip=comp;
    }
    
    int getNr_piese() const{ return nr_piese; };
    std::string getComp() const {return comp_princip; };
    
   friend std::ostream& operator<<(std::ostream &out, const Componente & comp){
        out<<"\nComponentele principale sunt: "<<comp.comp_princip<<"\n\n";
        return out;
    }
    friend std::istream& operator>>(std::istream& in, Componente& comp){
        std::cout<<" Numarul de componente: "; in>>comp.nr_piese;
        std::cout<<" Componentele principale: "; 
        in.ignore();
        std::getline(in,comp.comp_princip);
        return in;
    }

    Componente & operator=(const Componente & comp){
        nr_piese=comp.nr_piese;
        comp_princip=comp.comp_princip;
        return *this;
    }
    ~Componente(){}

};

class Mobila{
    std::string tip;
    Componente comp;
    int stoc, pret; 
    static int nr_actualizari;

    void stoc_redus(){
        char op;
        bool loop=true;
        while(loop){
            std::cout<<"\n Stocul este redus - doriti sa mariti pretul cu 5%? \n Tastati\n  'd' -> aplicarea scumpirii\n  'n' -> nemodificarea pretului\n";
            std::cin>>op;
            std::cin.ignore();
            if(op!='d' && op!='n')
                std::cout<<"\n Input invalid!\n";
            else{
                if(op=='d'){
                    setPret(pret*1.05);
                }
                loop=false;
            }
        }
    }
    
    public:
    Mobila(const std::string& tip_="", Componente &&comp_={0,""}, int stoc_=0, int pret_=0):
    tip{tip_}, comp{comp_}, stoc{stoc_}, pret{pret_} {}

    friend std::istream& operator>>(std::istream &in, Mobila& mob ){
        std::string linie;
        int x;
        std::getline(in,linie);
        mob.tip=linie;
        in>>x;
        in.ignore();
        std::getline(in,linie);
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
    
   friend std::ostream& operator<<(std::ostream & out, const Mobila& mob){ 
        
        out<<'\n'<<mob.tip<<'\n';
        out<<"Stocul disponibil: "<<mob.stoc<<'\n';
        out<<"Pretul: "<<mob.pret<<"\n";
        out<<"Numarul de componente: "<<mob.comp.getNr_piese()<<"\n";
        out<<"Componente principale: "<<mob.comp.getComp()<<"\n\n";
    
    return out;
    }

    inline std::string getTip() const{return tip;}

    void scrieFisier(std::ostream &out) const{
        out<<tip<<'\n';
        out<<comp.getNr_piese()<<'\n';
        out<<comp.getComp()<<'\n';
        out<<stoc<<'\n';
        out<<pret<<'\n';
    }

    void afisComp() const{ std::cout<<comp; }
    void setComp(){std::cin>>comp;}
    inline void setTip(const std::string &tip_){
        tip=tip_;
    }
    void setStoc(int stoc_){
        stoc=stoc_;
        if(stoc_<5)
            stoc_redus();
    }
    inline void setPret(int pret_){
        pret=pret_;
    }
    inline int getNrAct () const {return nr_actualizari;}
    inline void setNrAct() {nr_actualizari++;}

    Mobila(const Mobila& mob) :tip{mob.tip}, comp{mob.comp}, stoc{mob.stoc}, pret{mob.pret} {}

    Mobila & operator=(const Mobila & mob){

        tip=mob.tip;
        stoc=mob.stoc;
        pret=mob.pret;
        comp=mob.comp;
        return *this;
    }
    ~Mobila(){}
    
    int venit(const Clienti& cli){
        return pret*cli.getNrCl();
    }
};

int Mobila::nr_actualizari=0;

int main(){

    int total_mob,i;
    
    Mobila mobila[100];
    Clienti cli[100];
    
    std::ifstream f("date.in");
    if(!f){
        std::cout<<"Eroare - nu se poate deschide fisierul";
    }
    else{
    f>>total_mob;
    f.ignore();
    for(i=0;i<total_mob;++i){
        f>>mobila[i];
        f>>cli[i];
    }

    std::string input;
    int x,optiune;
    char ok;
    bool modificari=false;
    while(true){
    std::cout <<
    "--------------------------------------------------\n"
    "|                MENIU                            |\n"
    "--------------------------------------------------\n"
    "| 1  - Afisare detalii despre mobila             |\n"
    "| 2  - Afisati componentele principale           |\n"
    "| 3  - Afiseaza numarul de clienti               |\n"
    "| 4  - Adaugati mobilier                         |\n"
    "| 5  - Actualizati stocul mobilierului           |\n"
    "| 6  - Actualizati pretul mobilierului           |\n"
    "| 7  - Actualizati nr. clienti al mobilierului   |\n"
    "| 8  - Stergeti mobilier din inventar            |\n"
    "| 9  - Calculeaza venitul din vanzari            |\n"
    "| 10 - Afisati numarul de obiecte recent adaugate|\n"
    "| 11 - Iesire                                    |\n"
    "--------------------------------------------------\n"
    "Alegeti optiunea: ";
    
    std::getline(std::cin, input);
    try {
        optiune = std::stoi(input);
    } catch (...) {
        std::cout << "\n Introduceti un numar intre 1 si 10 \n";
        continue;
    }

    switch(optiune){
        case 1:
        std::cout<<" Tastati\n 1--> Afisati informatii despre TOT mobilierul \n 2--> Tastati numele piesei de mobilier \n";
        std::cin>>optiune;
        std::cin.ignore();
        if(optiune==1)
            for(i=0;i<total_mob;++i)
                std::cout<<mobila[i]<<cli[i];
        else if(optiune==2){
            ok=1;
           // std::cin.ignore();
            std::getline(std::cin, input);
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
        std::cout<<" Tastati numele piesei de mobilier \n";
        std::getline(std::cin, input);
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
    
    case 3:
        std::cout<<" Tastati\n 1--> Afiseaza numarul total de clienti \n 2--> Afiseaza numarul de clienti inregistrati pentru o piesa de mobilier \n";
        std::cin>>optiune;
        std::cin.ignore();

        if(optiune==1){
            unsigned int cnt=0;
            for(i=0;i<total_mob;++i)
                cnt+=cli[i].getNrCl();
            std::cout<<"Numar total de clienti : "<<cnt<<'\n';
        }
        else if(optiune==2){
            ok=1;

            std::getline(std::cin, input);
            for(i=0;i<total_mob;++i){
                if(input==cli[i].getTip()){
                    std::cout<<cli[i];
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
    
    case 4:
    if(total_mob>=100){
        std::cout<<"\nNu mai este loc in depozit pentru un tip nou de mobila!\n";
    }
    else{
        modificari=true;
        std::cout<<"\n Tipul mobilierului : "; 
        //std::cin.ignore();
        std::getline(std::cin, input);
        mobila[total_mob].setTip(input);
        cli[total_mob].setMobila(input);
        std::cout<<" Pretul: "; std::cin>>x;
        mobila[total_mob].setPret(x);
        std::cout<<" Stocul: "; 
        std::cin>>x;
        std::cin.ignore();
        mobila[total_mob].setStoc(x);
        mobila[total_mob].setComp();

        std::cout<<" Numarul de clienti: "; std::cin>>x;
        cli[total_mob].setNrClienti(x);
        total_mob++;
        mobila[0].setNrAct();
        //std::cin.ignore();
    }
    break;

    case 5:
        ok=1;
        std::cout<<"\n Tipul mobilierului: ";
        //std::cin.ignore();
        std::getline(std::cin, input);
            for(i=0;i<total_mob;++i){
                if(input==mobila[i].getTip()){
                    std::cout<<"\n Stocul actualizat: ";
                    std::cin>>x;
                    std::cin.ignore();
                    mobila[i].setStoc(x);

                    ok=0;
                    modificari=true;
                    break;
                }      
            }
        if(ok==1)
            std::cout<<"Input invalid - "<<input<<" nu exista in inventar\n";
        
    break;
    
    case 6:
        ok=1;
        std::cout<<"\n Tipul mobilierului: ";
        //std::cin.ignore();
        std::getline(std::cin, input);
            for(i=0;i<total_mob;++i){
                if(input==mobila[i].getTip()){
                    std::cout<<" Pretul actualizat: ";
                    std::cin>>x;
                    std::cin.ignore();
                    mobila[i].setPret(x);
                    ok=0;
                    modificari=true;
                    break;
                }      
            }
        if(ok==1)
            std::cout<<"Input invalid - "<<input<<" nu exista in inventar\n";
        break;

        case 7:
        ok=1;
        std::cout<<"\n Tipul mobilierului: ";
        //std::cin.ignore();
        std::getline(std::cin, input);
            for(i=0;i<total_mob;++i){
                if(input==cli[i].getTip()){
                    std::cout<<" Numar clienti: ";
                    std::cin>>x;
                    std::cin.ignore();
                    cli[i].setNrClienti(x);
                    ok=0;
                    modificari=true;
                    break;
                }      
            }
        if(ok==1)
            std::cout<<"Input invalid - "<<input<<" nu exista in inventar\n";
    break;

    case 8:
        ok=1;
        std::cout<<"\n Tipul mobilierului: ";
        //std::cin.ignore();
        std::getline(std::cin, input);
            for(i=0;i<total_mob;++i){
                if(input==mobila[i].getTip()){
                    for(int j=i;j<total_mob-1;--j)
                        mobila[j]=mobila[j+1];
                    ok=0;
                    total_mob--;
                    std::cout<<"\nInventarul a fost actualizat!\n";
                    modificari=true;

                }      
            }
        if(ok==1)
            std::cout<<"Input invalid - "<<input<<" nu exista in inventar\n";
    break;
    
    case 9:
    std::cout<<" Tastati\n 1--> Afisati venitul total \n 2--> Afisare venitul total din vanzarea unei singure piese de mobilier \n";
        std::cin>>optiune;
        std::cin.ignore();
        x=0;
        if(optiune==1){
            for(i=0;i<total_mob;i++)
                x+=mobila[i].venit(cli[i]);
            std::cout<<"\n Venit total din vanzari: "<<x<<'\n';
        }
        else if(optiune==2){
            ok=1;
            std::cout<<"Mobila : ";
            //std::cin.ignore();
            std::getline(std::cin, input);
            for(i=0;i<total_mob;++i){
                if(input==mobila[i].getTip()){
                    x=mobila[i].venit(cli[i]);
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
    
    case 10:
    std::cout<<"Numarul pieselor de mobilier recent adaugate: \n";   
    std::cout<<mobila[0].getNrAct()<<'\n';
    break; 

    case 11:{
    f.close();
    if(modificari==true){
        std::ofstream g("date.in");
        g<<total_mob<<'\n';
        for(i=0;i<total_mob;++i){
            mobila[i].scrieFisier(g);
            cli[i].scrieFisier(g);
        }
        g.close();
    }
    return 0;
    break;
}

    default:
    std::cout<<"\nTastati un numar intre 1 si 10\n";
    break;
}
}
}
return 0;

}