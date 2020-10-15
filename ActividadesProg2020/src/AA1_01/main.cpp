#include "Enemy.h"


void enemyListReader(std::vector<Enemy>& enemyVec)
{
	rapidxml::xml_document<> doc;
	std::ifstream file("config.xml");
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str());
	doc.parse<0>(&content[0]);

	rapidxml::xml_node<>* pRoot = doc.first_node();


	for (rapidxml::xml_node<>* pNode = pRoot->first_node(); pNode; pNode = pNode->next_sibling())
	{
		Enemy newEnemy;
		newEnemy.enemyName = pNode->first_attribute()->value();
		for (rapidxml::xml_node<>* pNodeI = pNode->first_node(); pNodeI; pNodeI = pNodeI->next_sibling())
		{
			
			std::cout << pNodeI->name() << ":" << pNodeI->value() << std::endl;
			newEnemy.vitality = atoi(pNodeI->value());
			newEnemy.damage = atoi(pNodeI->value());
			newEnemy.defense = atoi(pNodeI->value());
			newEnemy.atackFrequency = atoi(pNodeI->value());
			newEnemy.exp = atoi(pNodeI->value());
			//Hacer weapons 
		}
		enemyVec.push_back(newEnemy);
	}
}

int main()
{
	std::vector<Enemy> enemyList;
	enemyListReader(enemyList);
	return 0;
}

