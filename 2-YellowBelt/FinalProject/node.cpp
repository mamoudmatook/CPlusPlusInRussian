#include "node.h"

EmptyNode::EmptyNode() {}
bool EmptyNode::Evaluate(const Date& date, const std::string& event) const
{
	return true;
}
DateComparisonNode::DateComparisonNode(const Comparison& comprs, const Date& date) : cmpr(comprs), dt(date) {}
bool DateComparisonNode::Evaluate(const Date& date, const std::string& event) const
{
	switch (cmpr)
	{
	case Comparison::Less:
		return date < dt;	
	case Comparison::LessOrEqual:
		return date <= dt;	
	case Comparison::Greater:
		return date > dt;	
	case Comparison::GreaterOrEqual:
		return date >= dt;	
	case Comparison::Equal:
		return date == dt;	
	case Comparison::NotEqual:
		return date != dt;
	default:
		return 0;
		break;
	}
}
EventComparisonNode::EventComparisonNode(const Comparison& comprs, const std::string& event) : cmpr(comprs), evnt(event) {}
bool EventComparisonNode::Evaluate(const Date& date, const std::string& event) const
{
	switch (cmpr)
	{
	case Comparison::Less:
		return event < evnt;
	case Comparison::LessOrEqual:
		return event <= evnt;
	case Comparison::Greater:
		return event > evnt;
	case Comparison::GreaterOrEqual:
		return event >= evnt;
	case Comparison::Equal:
		return event == evnt;
	case Comparison::NotEqual:
		return event != evnt;
	default:
		return 0;
		break;
	}
}

LogicalOperationNode::LogicalOperationNode(const LogicalOperation& logical_operation, 
										   const std::shared_ptr<Node>& lhs, 
										   const std::shared_ptr<Node>& rhs) : lgc_op(logical_operation),
										   lhs_node(lhs), rhs_node(rhs)
{
}
bool LogicalOperationNode::Evaluate(const Date& date, const std::string& event) const
{
	switch (lgc_op)
	{
	case LogicalOperation::Or:
		return lhs_node->Evaluate(date, event) || rhs_node->Evaluate(date, event);
	case LogicalOperation::And:
		return lhs_node->Evaluate(date, event) && rhs_node->Evaluate(date, event);
	default:
		return false;
		break;
	}
}