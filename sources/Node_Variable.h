#pragma once

#include "Nodable.h"
#include "Node_Value.h"
#include <string>

namespace Nodable{
	/* Node_Variable is a node that identify a value with its name */
	class Node_Variable : public Node_Value{
	public:
		Node_Variable(const char* _label, Node* _target = nullptr);
		~Node_Variable();
		void            draw();

		void            setValue        (Node* _node)override;
		void            setValue        (const char* /*value*/)override;
		void            setValue        (double /*value*/)override;

		Node* 	        getValueAsNode  ()override;
		double          getValueAsNumber()const override;
		std::string     getValueAsString()const override;

		std::string     getLabel        ()const;
	private:
		Node*       target;
		std::string label;
	};
}