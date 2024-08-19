#pragma once

/*class Physics {
public:
	static float Speedx()         { return 3;    }
	static float maxSpeedx()      { return 12;   }

	static float airFriction()    { return 0.1f; }
	static float groundFriction() { return 0.3f; }

	static float jumpSpeed()      { return 7;    }
	static float gravity()        { return 0.4;  }
	static float maxSpeedy()      { return 16;   }
};*/
namespace Physics {
	const float Speedx = 3;
	const float maxSpeedx = 12;

	const float airFriction = 0.1;
	const float groundFriction = 0.3;

	const float jumpSpeed = 14;
	const float gravity = 0.4;
	const float maxSpeedy = 16;
}
