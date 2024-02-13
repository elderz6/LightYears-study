#include "framework/World.h"
#include "framework/MathUtility.h"
#include "VFX/Particle.h"
#include "VFX/Explosion.h"

namespace ly
{
	Explosion::Explosion(int particleAmt, float lifeTimeMin, float lifeTimeMax, float sizeMin, float sizeMax, float speedMin, float speedMax,
		const sf::Color& particleColor,
		const List<std::string>& particleImagePaths)
		:m_particleAmt{ particleAmt },
		m_lifeTimeMin{ lifeTimeMin },
		m_lifeTimeMax{ lifeTimeMax },
		m_sizeMin{ sizeMin },
		m_sizeMax{ sizeMax },
		m_speedMin{ speedMin },
		m_speedMax{ speedMax },
		m_particleColor { particleColor },
		m_particleImagePaths{ particleImagePaths }
	{
	}

	void Explosion::SpawnExplosion(World* world, const sf::Vector2f& location)
	{
		if (!world) return;

		for (int i = 0; i < m_particleAmt; i++)
		{
			std::string particleImagePath = m_particleImagePaths[(int)RandomRange(0, m_particleImagePaths.size())];
			weak<Particle> newParticle = world->SpawnActor<Particle>(particleImagePath);
			newParticle.lock()->RandomLifetime(m_lifeTimeMin, m_lifeTimeMax);
			newParticle.lock()->SetActorLocation(location);
			newParticle.lock()->RandomSize(m_sizeMin, m_sizeMax);
			newParticle.lock()->RandomVelocity(m_speedMin, m_speedMax);
			newParticle.lock()->GetSprite().setColor(m_particleColor);
		}
	}
}