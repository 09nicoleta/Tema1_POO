#include<iostream>
#include<utility>
#include<string>
#include<fstream>

class Clienti{
    
    std::string mobila;
    int nr_cl;
    
    public:
    Clienti(const std::string& mob="", int nr_cl=0):
    mobila(mob), nr_cl{nr_cl} {};



    void setMobila(const std::string& mobila){
        this->mobila=mobila;
    }

    void setNrClienti(int nr_cl){
        this->nr_cl=nr_cl;
    }

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

    Componente(const Componente &comp): nr_piese{comp.nr_piese}, comp_princip{comp.comp_princip}{

    }

    Componente(Componente &&comp) : 
    nr_piese{std::move(comp.nr_piese)}, comp_princip{std::move(comp.comp_princip)} {};
    


    void setNr_piese(unsigned int nr){
        nr_piese=nr;
    }

    void setComp(const std::string& comp){
        comp_princip=comp;
    }
    
    int getNr_piese() const{ return nr_piese; };
    std::string getComp() const {return comp_princip; };

};

class Mobila{
    std::string tip;
    Componente comp;
    unsigned int stoc, pret; 
    
    public:
    Mobila(const std::string& tip_="", Componente &&comp_={0,""}, unsigned int stoc_=0, unsigned int pret_=0):
    tip{tip_}, comp{std::move(comp_)}, stoc{stoc_}, pret{pret_} {};

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
        
        out<<mob.tip<<'\n';
        out<<"Stocul disponibil: "<<mob.stoc<<'\n';
        out<<"Pretul: "<<mob.pret<<"\n";
        out<<"Numarul de componente principale: "<<mob.comp.getNr_piese()<<"\n";
        out<<"Componente principale: "<<mob.comp.getComp()<<"\n\n";
    
    return out;
    }

    void scrieFisier(std::ostream &out, int total_mob) const{
        out<<total_mob<<'\n';
        out<<tip<<'\n';
        out<<comp.getNr_piese()<<'\n';
        out<<comp.getComp()<<'\n';
        out<<stoc<<'\n';
        out<<pret<<'\n';
    }
 
};

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
        std::cout<<mobila[i];
    }

    f.close();
    
}
    return 0;
}