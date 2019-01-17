#ifndef HEXBOARD_H
#define HEXBOARD_H

#include <QList>
#include "Hex.h"

/**
 * @brief
 *
 */
class HexBoard{
public:
    // constructors
    /**
     * @brief
     *
     */
    HexBoard();

    // getters/setters
    /**
     * @brief
     *
     * @return QList<Hex *>
     */
    QList<Hex*> getHexes();

    // public methods
    /**
     * @brief
     *
     * @param x
     * @param y
     * @param cols
     * @param rows
     */
    void placeHexes(int x, int y, int cols, int rows);

private:
    /**
     * @brief
     *
     * @param x
     * @param y
     * @param numOfRows
     */
    void createHexColumn(int x, int y, int numOfRows);
    QList<Hex*> hexes; /**< TODO: describe */
};

#endif // HEXBOARD_H
