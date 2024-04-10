#ifndef __ANIMATION_H
#define __ANIMATION_H

class Animation {
public:
	struct Frame {
		sf::IntRect rect;
		double duration;
	};

	enum Mode {
		LOOP,
		SINGLE,
	};

	Animation(sf::Sprite& target);

	virtual ~Animation();

	void addFrame(Frame&& frame);

	void setMode(Mode mode);

	const Mode& getMode() const;

	void update(double elapsed);

	void animate();

	const double getLength() const;

private:
	std::vector<Frame> m_frames;
	double m_total_length;
	double m_progress;
	sf::Sprite& m_target;
	Mode m_mode;
};

#endif /* __ANIMATION_H */