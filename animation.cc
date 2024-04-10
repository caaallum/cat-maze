#include <SFML/Graphics.hpp>

#include "animation.h"

Animation::Animation(sf::Sprite& target) :
	m_target(target),
	m_mode(SINGLE) {
	m_progress = m_total_length = 0.0f;
}

Animation::~Animation() {

}

void
Animation::addFrame(Frame&& frame) {
	m_total_length += frame.duration;
	m_frames.push_back(std::move(frame));
}

void
Animation::setMode(Mode mode) {
	m_mode = mode;
}

const Animation::Mode&
Animation::getMode() const {
	return m_mode;
}

void
Animation::update(double elapsed) {
    m_progress += elapsed;
    double p = m_progress;
    for (size_t i = 0; i < m_frames.size(); i++) {
        if (m_mode == LOOP && p > 0.0 && &(m_frames[i]) == &(m_frames.back())) {
            i = 0;    // start over from the beginning
            continue; // break off the loop and start where i is
        }

        p -= m_frames[i].duration;

        // if we have progressed OR if we're on the last frame, apply and stop.
        if (p <= 0.0 || &(m_frames[i]) == &m_frames.back())
        {
            m_target.setTextureRect(m_frames[i].rect);
            break; // we found our frame
        }
    }
}

void
Animation::animate() {
    sf::Clock duration;
    for (const auto& frame : m_frames) {
        m_target.setTextureRect(frame.rect);
        while (duration.getElapsedTime().asSeconds() < frame.duration);
        duration.restart();
    }
}

const double
Animation::getLength() const {
    return m_total_length;
}