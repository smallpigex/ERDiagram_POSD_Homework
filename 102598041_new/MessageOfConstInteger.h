#pragma once

namespace ConnectMessage
{
	const int CAN_CONNECT = 1;
	const int IS_CARDINALITY = 2;
	const int ITSELF = -1;
	const int CAN_NOT_CONNECT = -2;
	const int HAS_BEEN_CONNECT = -3;
	const int HAS_BEEN_CONNECT_OTHER_NODE = -4;
	const int SAME_TYPE = -5;
}

namespace NotGet
{
	const int ID = -1;
}

const int nullComponentId = -1;
const int tmpComponentId = -2;