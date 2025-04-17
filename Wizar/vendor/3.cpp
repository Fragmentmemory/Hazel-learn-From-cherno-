// 画面分块调度策略（伪代码）
void dispatchTiles(const Frame& frame) {
    const int TILE_SIZE = 256;
    std::vector<Tile> tiles;
    
    for(int y=0; y<frame.height; y+=TILE_SIZE){
        for(int x=0; x<frame.width; x+=TILE_SIZE){
            tiles.emplace_back(x, y, TILE_SIZE, TILE_SIZE);
        }
    }
    
    // 分配tile到渲染节点
    distributeWorkloads(tiles);
}