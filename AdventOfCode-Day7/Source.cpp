//DAY 7 HAS NOT BEEN COMPLETED, THIS WAS CODE WRITTEN BY SOMEONE ELSE

#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <algorithm>
#include <cctype>
#include <cstdint>

enum OPS {
	OP_ERR, OP_AND, OP_OR, OP_NOT, OP_LSHIFT, OP_RSHIFT, OP_STORE
};

bool isnumber(const std::string &n) {
	return std::all_of(n.begin(), n.end(), ::isdigit);
}

OPS stoop(const std::string s) {
	if (s == "AND")
		return OP_AND;
	else if (s == "OR")
		return OP_OR;
	else if (s == "LSHIFT")
		return OP_LSHIFT;
	else if (s == "RSHIFT")
		return OP_RSHIFT;
	else
		return OP_ERR;
}

using stype = std::uint16_t;

struct gate {
	OPS op;
	std::string lhs;
	std::string rhs;
	bool memoized;
	stype val;
	gate(void) : op(OP_ERR), lhs(""), rhs(""), memoized(false), val(0) {}
};

class logic {
	std::map<std::string, gate> circuit;
	stype output_of(const std::string &);
public:
	stype find_output(const std::string &);
	void dump(void);
	void reset(void);
	std::map<std::string, gate>::size_type size(void) { return circuit.size(); }
	void add(const std::string &wire, gate g) { circuit[wire] = g; }
	gate& find_gate(const std::string &wire) { return circuit[wire]; }
};

stype logic::output_of(const std::string &num_or_wire) {
	if (isnumber(num_or_wire))
		return std::stoi(num_or_wire);
	else
		return find_output(num_or_wire);
}

stype logic::find_output(const std::string &wire) {
	if (circuit.find(wire) == circuit.end()) {
		std::cerr << "Unknown wire '" << wire << "'\n";
		return 0;
	}

	gate &g = circuit[wire];
	if (g.memoized) {
		return g.val;
	}
	else {
		stype r;
		switch (g.op) {
		case OP_ERR:
			std::cerr << "Unknown gate operation for wire " << wire << '\n';
			return 0;
		case OP_STORE:
			r = output_of(g.lhs);
			break;
		case OP_AND:
			r = output_of(g.lhs) & output_of(g.rhs);
			break;
		case OP_OR:
			r = output_of(g.lhs) | output_of(g.rhs);
			break;
		case OP_LSHIFT:
			r = output_of(g.lhs) << output_of(g.rhs);
			break;
		case OP_RSHIFT:
			r = output_of(g.lhs) >> output_of(g.rhs);
			break;
		case OP_NOT:
			r = ~output_of(g.lhs);
			break;
		}
		g.memoized = true;
		g.val = r;
		return r;
	}
}

void logic::dump(void) {
	for (auto &wires : circuit)
		std::cout << wires.first << ": " << find_output(wires.first) << '\n';
}

void logic::reset(void) {
	for (auto &gate : circuit)
		gate.second.memoized = false;
}

int main(void) {
	std::string command;
	logic circuit;
	std::regex assign_op{ "(\\w+) -> (\\w+)" };
	std::regex not_op{ "NOT (\\w+) -> (\\w+)" };
	std::regex binary_op{ "(\\w+) (AND|OR|LSHIFT|RSHIFT) (\\w+) -> (\\w+)" };

	while (std::getline(std::cin, command)) {
		std::smatch fields;
		gate g;
		if (std::regex_match(command, fields, assign_op)) {
			g.op = OP_STORE;
			g.lhs = fields[1];
			circuit.add(fields[2], g);
		}
		else if (std::regex_match(command, fields, not_op)) {
			g.op = OP_NOT;
			g.lhs = fields[1];
			circuit.add(fields[2], g);
		}
		else if (std::regex_match(command, fields, binary_op)) {
			g.op = stoop(fields[2]);
			g.lhs = fields[1];
			g.rhs = fields[3];
			circuit.add(fields[4], g);
		}
		else {
			std::cerr << "Unknown gate: " << command << '\n';
		}
	}

	std::cout << "There are a total of " << circuit.size() << " gates.\n";

	stype a = circuit.find_output("a");
	std::cout << "Initial value of a: " << a << '\n';

	circuit.reset();
	gate b;
	b.op = OP_STORE;
	b.lhs = std::to_string(a);
	b.memoized = true;
	b.val = a;
	circuit.add("b", b);

	a = circuit.find_output("a");
	std::cout << "New value of a: " << a;

	return 0;
}