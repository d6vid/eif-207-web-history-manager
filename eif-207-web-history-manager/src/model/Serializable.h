#pragma once

class Serializable {
	virtual bool serialize(std::ofstream& out) = 0;
	virtual bool deserialize(std::ifstream& in) = 0;
};