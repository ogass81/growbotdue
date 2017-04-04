// 
// 
// 

#include "Ruleset.h"

RuleSet::RuleSet(int count)
{
	title = String(count);
	reset();
}

void RuleSet::changeRuleSetTrigger1()
{
	uint8_t cat = triggercat1_ptr;
	uint8_t set = triggerset1_ptr;

	//Cycle through active triggers
	while (true) {
		if (set == TRIGNUMBER - 1) {
			set = 0;

			if (cat < TRIGCAT) cat++;
			else cat = 0;
		}
		else if (set == TRIGNUMBER) {
			set = 0;
			cat = 0;
		}
		else {
			set++;
		}
		
		if (cat == TRIGCAT) {
			assignedTrigger[0] = NULL;
			set = TRIGNUMBER;
			break;
		}
		else if (trigger[cat][set]->active == true) {
			assignedTrigger[0] = trigger[cat][set];
			break;
		}
	}
	triggercat1_ptr = cat;
	triggerset1_ptr = set;
}

void RuleSet::changeRuleSetTrigger2()
{
	uint8_t cat = triggercat2_ptr;
	uint8_t set = triggerset2_ptr;

	//Cycle through active triggers
	while (true) {
		if (set == TRIGNUMBER - 1) {
			set = 0;

			if (cat < TRIGCAT) cat++;
			else cat = 0;
		}
		else if (set == TRIGNUMBER) {
			set = 0;
			cat = 0;
		}
		else {
			set++;
		}

		if (cat == TRIGCAT) {
			assignedTrigger[1] = NULL;
			set = TRIGNUMBER;
			break;
		}
		else if (trigger[cat][set]->active == true) {
			assignedTrigger[1] = trigger[cat][set];
			break;
		}
	}
	triggercat2_ptr = cat;
	triggerset2_ptr = set;
}

void RuleSet::changeRuleSetTrigger3()
{
	uint8_t cat = triggercat3_ptr;
	uint8_t set = triggerset3_ptr;

	//Cycle through active triggers
	while (true) {
		if (set == TRIGNUMBER - 1) {
			set = 0;

			if (cat < TRIGCAT) cat++;
			else cat = 0;
		}
		else if (set == TRIGNUMBER) {
			set = 0;
			cat = 0;
		}
		else {
			set++;
		}

		if (cat == TRIGCAT) {
			assignedTrigger[2] = NULL;
			set = TRIGNUMBER;
			break;
		}
		else if (trigger[cat][set]->active == true) {
			assignedTrigger[2] = trigger[cat][set];
			break;
		}
	}
	triggercat3_ptr = cat;
	triggerset3_ptr = set;
}

void RuleSet::changeRuleSetBoolOp1()
{
	if (assignedBoolOp[0] == NOT) assignedBoolOp[0] = AND;
	else if (assignedBoolOp[0] == AND) assignedBoolOp[0] = OR;
	else assignedBoolOp[0] = NOT;
}

void RuleSet::changeRuleSetBoolOp2()
{
	if (assignedBoolOp[1] == NOT) assignedBoolOp[1] = AND;
	else if (assignedBoolOp[1] == AND) assignedBoolOp[1] = OR;
	else assignedBoolOp[1] = NOT;
}

void RuleSet::changeRuleChain()
{
	uint8_t action = chain_ptr;

	//Cycle through actionchains
	while (true) {
		if (action == ACTIONCHAINS) {
			action = 0;
		}
		else {
			action++;
		}

		if (action == ACTIONCHAINS) {
			assignedChain = NULL;
			break;
		}
		else if (actionchains[action]->active == true) {
			assignedChain = actionchains[action];
			break;
		}
	}
	chain_ptr = action;
}

void RuleSet::changeRuleSetActive()
{
	if(active == true) active = false;
	else active = true;
}

String RuleSet::getTitle()
{
	return String("Ruleset #" + title);
}

String RuleSet::getRuleSetCat1()
{
	return String(F("<NONE>"));
}

String RuleSet::getRuleSetCat2()
{

 return String(F("<NONE>"));
}

String RuleSet::getRuleSetCat3()
{
	return String(F("<NONE>"));
}

String RuleSet::getRuleSetTrigger1()
{
	if (assignedTrigger[0] != NULL) {
		return String(assignedTrigger[0]->getTitle());
	}
	else return String(F("<NONE>"));
}

String RuleSet::getRuleSetTrigger2()
{
	if (assignedTrigger[1] != NULL) {
		return String(assignedTrigger[1]->getTitle());
	}
	else return String(F("<NONE>"));
}

String RuleSet::getRuleSetTrigger3()
{
	if (assignedTrigger[2] != NULL) {
		return String(assignedTrigger[2]->getTitle());
	}
	else return String(F("<NONE>"));
}

String RuleSet::getRuleSetBoolOp1()
{
	if (assignedBoolOp[0] == AND) return String(F("AND"));
	else if (assignedBoolOp[0] == OR) return String(F("OR"));
	else return String(F("NOT"));
}

String RuleSet::getRuleSetBoolOp2()
{
	if (assignedBoolOp[1] == AND) return String(F("AND"));
	else if (assignedBoolOp[1] == OR) return String(F("OR"));
	else return String(F("NOT"));
}

String RuleSet::getRuleSetChain()
{
	if (assignedChain != NULL) return String(assignedChain->getTitle());
	else return String(F("<NONE>"));
}


String RuleSet::getRuleSetActive()
{
	if (active == true) return String(F("ON"));
	else return String(F("OFF"));
}

bool RuleSet::checkState()
{
	bool state = false;
	uint8_t i = 0;

	if (active == true) {
		while (assignedTrigger[i] != NULL) {
			if (i == 0) {
				state = assignedTrigger[i]->checkState();
				LOGDEBUG(F("[Ruleset]"), F("checkstate()"), F("OK: First Trigger"), String(assignedTrigger[i]->getTitle()), String(state), "");
			}
			else {
				if (assignedTrigger[i - 1] != NULL) {

					switch (assignedBoolOp[i - 1]) {

					case AND:
						state = state && assignedTrigger[i]->checkState();
						LOGDEBUG(F("[Ruleset]"), F("checkstate()"), F("OK: AND Next Trigger"), String(assignedTrigger[i]->getTitle()), String(state), "");
						break;

					case OR:
						state = state || assignedTrigger[i]->checkState();
						LOGDEBUG(F("[Ruleset]"), F("checkstate()"), F("OK: OR Next Trigger"), String(assignedTrigger[i]->getTitle()), String(state), "");
						break;

					case NOT:
						state = state && !assignedTrigger[i]->checkState();
						LOGDEBUG(F("[Ruleset]"), F("checkstate()"), F("OK: NOT Next Trigger"), String(assignedTrigger[i]->getTitle()), String(state), "");
						break;
					}
				}
				else LOGDEBUG(F("[Ruleset]"), F("checkstate()"), F("ERROR: No previous Trigger in Ruleset"), F("Final State @"), String(i), String(state));
			}
			i++;
		}
	}
	return state;
}

void RuleSet::reset()
{
	active = false;

	assignedTrigger[0] = NULL;
	assignedTrigger[1] = NULL;
	assignedTrigger[2] = NULL;

	assignedBoolOp[0] = AND;
	assignedBoolOp[1] = AND;

	assignedChain = NULL;

	triggercat1_ptr = TRIGCAT;
	triggercat2_ptr = TRIGCAT;
	triggercat3_ptr = TRIGCAT;
	triggerset1_ptr = TRIGNUMBER;
	triggerset2_ptr = TRIGNUMBER;
	triggerset3_ptr = TRIGNUMBER;

	chain_ptr = ACTIONCHAINS;
}

void RuleSet::serializeJSON(uint8_t id, char * json, size_t maxSize)
{
	StaticJsonBuffer<500> jsonBuffer;

	JsonObject& rules = jsonBuffer.createObject();

	rules["type"] = "RULE";
	rules["id"] = id;
	rules["active"] = active;
	rules["tset1_ptr"] = triggerset1_ptr;
	rules["tcat1_ptr"] = triggercat1_ptr;
	rules["tset2_ptr"] = triggerset2_ptr;
	rules["tcat2_ptr"] = triggercat2_ptr;
	rules["tset3_ptr"] = triggerset3_ptr;
	rules["tcat3_ptr"] = triggercat3_ptr;
	rules["chain_ptr"] = chain_ptr;

	JsonArray& boolop = rules.createNestedArray("Bool");
	boolop.add(static_cast<int>(assignedBoolOp[0]));
	boolop.add(static_cast<int>(assignedBoolOp[1]));

	rules.printTo(json, maxSize);
	LOGDEBUG(F("[Ruleset]"), F("serializeJSON()"), F("OK: Serialized Members for Ruleset"), String(id), String(rules.measureLength()), String(maxSize));
}

bool RuleSet::deserializeJSON(JsonObject & data)
{
	if (data.success() == true) {
		this->active = data["active"];
		this->triggerset1_ptr = data["tset1_ptr"];
		this->triggercat1_ptr = data["tcat1_ptr"];
		this->triggerset2_ptr = data["tset2_ptr"];
		this->triggercat2_ptr = data["tcat2_ptr"];
		this->triggerset3_ptr = data["tset3_ptr"];
		this->triggercat3_ptr = data["tcat3_ptr"];
		this->chain_ptr = data["chain_ptr"];
		
		//Assigning Pointers
		if (data["Bool"][0] == 0) assignedBoolOp[0] = AND;
		else if (data["Bool"][0] == 1) assignedBoolOp[0] = OR;
		else if (data["Bool"][0] == 2) assignedBoolOp[0] = NOT;
		else {
			assignedBoolOp[0] = OR;
			active = false;
		}
		
		if (data["Bool"][1] == 0) assignedBoolOp[1] = AND;
		else if (data["Bool"][1] == 1) assignedBoolOp[1] = OR;
		else if (data["Bool"][1] == 2) assignedBoolOp[1] = NOT;
		else {
			assignedBoolOp[1] = OR;
			active = false;
		}

		if (triggerset1_ptr != TRIGNUMBER && triggercat1_ptr != TRIGCAT) assignedTrigger[0] = trigger[triggercat1_ptr][triggerset1_ptr];
		else assignedTrigger[0] = NULL;
		if (triggerset2_ptr != TRIGNUMBER && triggercat2_ptr != TRIGCAT) assignedTrigger[1] = trigger[triggercat2_ptr][triggerset2_ptr];
		else assignedTrigger[1] = NULL;
		if (triggerset3_ptr != TRIGNUMBER && triggercat3_ptr != TRIGCAT) assignedTrigger[2] = trigger[triggercat3_ptr][triggerset3_ptr];
		else assignedTrigger[2] = NULL;
		if (chain_ptr != ACTIONCHAINS) assignedChain = actionchains[chain_ptr];
		else assignedChain = NULL;

		LOGDEBUG(F("[Ruleset]"), F("deserializeJSON()"), F("OK: Deserialized members for Ruleset"), data["id"].asString(), F("Datasize"), String(data.size()));
	}
	else {
		LOGDEBUG(F("[Ruleset]"), F("deserializeJSON()"), F("ERROR: No Data to deserialize membersRuleset"), F("Datasize"), String(data.size()), "");
	}
	return data.success();
}

void RuleSet::execute()
{
	if (checkState() == true) {
		if(assignedChain != NULL) {
			assignedChain->execute();
		}
	}
}