#pragma once

class ILayer {
	~ILayer();

	virtual void OnUpdate() = 0;
	virtual void OnAttach() = 0;
	virtual void OnEvent() = 0;
};


