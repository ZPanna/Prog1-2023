#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <list>
#include <vector>

enum Weapon {
    KALAPACS,
    KETELUFEJSZE,
    FEJSZE,
    POROLY
};

static std::unordered_map<std::string, Weapon> const WEAPON_MAP = {
    {"KALAPACS", Weapon::KALAPACS},
    {"KETELUFEJSZE", Weapon::KETELUFEJSZE},
    {"FEJSZE", Weapon::FEJSZE},
    {"POROLY", Weapon::POROLY}
};

static Weapon weapon_from_string(const std::string& from) {
    auto it = WEAPON_MAP.find(from);
    if (it == WEAPON_MAP.end()) return Weapon::KALAPACS;
    return it->second;
}

class Orc {
    int m_id;
    std::string m_name;
    int name_set_counter = 0;
    int m_vitality;
    bool m_died;
    Weapon m_weapon;
    int m_damage;
    bool damage_assign = false;
    int m_shield;

public:
    Orc(int id, std::string name, int vitality, bool died, Weapon weapon, int damage, int shield) {
        this->m_id = id;
        this->name(name);
        this->m_vitality = vitality;
        this->m_died = died;
        this->m_weapon = weapon;
        this->damage(damage);
        this->shield(shield);
    }

    void damaged(int damage) {
        this->m_damage -= damage;
        if (damage <= 0) this->m_died = true;
    }

    void attack(Orc& other) {
        if (other.died()) {
            std::cout << "A hullagyalázásra még egy ork sem képes!" << std::endl;
        } else {
            other.damaged(this->damage());
        }
    }

    std::string to_string() {
        std::ostringstream builder;
        builder << "id: " << this->id() 
        << ", name: " << this->name() 
        << ", vitality: " << this->vitality() 
        << ", died: " << this->died() 
        << ", weapon: " << this->weapon() 
        << ", damage: " << this->damage() 
        << ", shield: " << this->shield();
        return builder.str();
    }

    int id() const {
        return m_id;
    }

    std::string name() const {
        return m_name;
    }

    int vitality() const {
        return m_vitality;
    }

    bool died() const {
        return m_died;
    }

    Weapon weapon() const {
        return m_weapon;
    }

    int damage() const {
        return m_damage;
    }

    int shield() const {
        return m_shield;
    }

    void name(const std::string& name) {
        if (++name_set_counter > 3) return;
        this->m_name = name;
    }

private:
    void damage(const int& damage) {
        if (!damage_assign && damage >= 20 && damage < 50) {
            this->m_damage = damage;
        }
    }

    void shield(const int& shield) {
        if (shield >= 10 && shield <= 20)
            this->m_shield = shield;
    }
};

class Horde {
    std::string name;
    std::list<Orc> orcs;

public:
    Horde(std::string name) : name(name), orcs() {}

    void add_orc(int id, std::string name, int vitality, bool died, Weapon weapon, int damage, int shield) {
        orcs.push_back(Orc(id, name, vitality, died, weapon, damage, shield));
    }

    std::list<Orc> dead_orcs() {
        std::list<Orc> dead;
        for (const auto& orc : orcs) {
            if (orc.died())
                dead.push_back(orc);
        }
        return dead;
    }

    Orc strongest_orc() {
        Orc strongest = *orcs.begin();
        for (const Orc& orc : orcs) {
            if (orc.damage() > strongest.damage())
                strongest = orc;
        }
        return strongest;
    }

    std::list<Orc> weak_orcs(int vitality) {
        std::list<Orc> weak;
        for (const auto& orc : orcs) {
            if (orc.vitality() < vitality)
                weak.push_back(orc);
        }
        return weak;
    }

    std::list<Orc> with_weapon(Weapon weapon) {
        std::list<Orc> matched;
        for (const auto& orc : orcs) {
            if (orc.weapon() == weapon)
                matched.push_back(orc);
        }
        return matched;
    }
};

std::vector<std::string> split(const std::string &s, char delim) {
  std::stringstream ss(s);
  std::string item;
  std::vector<std::string> elems;
  while (std::getline(ss, item, delim)) {
     elems.push_back(std::move(item));
  }
  return elems;
}

int main() {
    Horde horde {"gyenge banda"};
    
    std::ifstream input {"ork.csv"};
    std::string line;
    
    std::getline(input, line);
    int id = 1;
    while (std::getline(input, line)) {
        auto data = split(line, ';');

        std::string name = data[0];
        int vitality = std::stoi(data[1]);
        Weapon weapon = weapon_from_string(data[2]);
        int damage = std::stoi(data[3]);
        int shield = std::stoi(data[4]);

        horde.add_orc(id++, name, vitality, vitality <= 0, weapon, damage, shield);
    }

    std::cout << "Legerősebb ork: " << horde.strongest_orc().to_string() << std::endl;

    std::cout << "Halott orkok:" << std::endl;
    for (auto& orc : horde.dead_orcs())
        std::cout << orc.to_string() << std::endl;

    int weak = 40;
    std::cout << "Orkok kevesebb mint " << weak << " életerővel:" << std::endl;
    for (auto& orc : horde.weak_orcs(weak))
        std::cout << orc.to_string() << std::endl;

    Weapon weapon = Weapon::KALAPACS;
    std::cout << "Orkok a következő fegyverrel:" << weapon << std::endl;
    for (auto& orc : horde.with_weapon(weapon))
        std::cout << orc.to_string() << std::endl;
}