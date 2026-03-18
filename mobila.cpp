#include<iostream>
#include<utility>
#include<string>

class Clienti{
    
    std::string mobila;
    unsigned int nr_cl;
    public:
    Clienti(const std::string& mob, unsigned int nr_cl=0):
    mobila(mob), nr_cl{nr_cl} {};
};

class Componente{
    unsigned int nr_piese;
    std::string comp_princip;
    
    public:
    Componente(unsigned int nr_piese=0, const std::string& comp_pr="") : 
    nr_piese{nr_piese}, comp_princip(comp_pr) {};

    Componente(Componente &&comp) : 
    nr_piese{std::move(comp.nr_piese)}, comp_princip{std::move(comp.comp_princip)} {};
    
};

class Mobila{
    Componente comp;
    unsigned int stoc,pret; 
    std::string tip;
    
    public:

    Mobila(unsigned int stoc_=0, unsigned int pret_=0, const std::string& tip_="", Componente &&comp_={0,""}):
    stoc{stoc_}, pret{pret_}, tip{tip_}, comp{std::move(comp_)}{};

};

int main(){


    return 0;
}
