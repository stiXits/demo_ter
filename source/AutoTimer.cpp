
#include <cassert>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <iomanip>
#include <sstream>

#include <QDebug>

#include "Timer.h"
#include "AutoTimer.h"


int AutoTimer::m_numActiveInstances(0);

AutoTimer::AutoTimer(const char * info)
:   m_info(info)
,   m_index(++m_numActiveInstances)
,   m_timer(new Timer(false))
{
    m_timer->start();
}

AutoTimer::~AutoTimer()
{
    m_timer->pause();

    double delta(static_cast<double>(m_timer->elapsed()));

    // use number of digits to retrieve exp in 10^(3 exp)
    static const char * units("num ");

    const unsigned char u(std::min<char>(3, static_cast<char>(ceil(log10(delta) / 3.0))));

    std::string unit = "s";

    if (u < 3)
        unit.insert(0, 1, units[u]);

    // shorten the time to nearest time unit
    delta /= pow(1000.0, u);

    std::stringstream s;
    s << m_info << " took " << std::setprecision(4) << delta << unit
        << " (timer_" << std::setfill('0') << std::setw(2) << m_index << ").";

    qDebug() << QString::fromStdString(s.str());

    delete m_timer;

    assert(0 < m_numActiveInstances);
    --m_numActiveInstances;
}
