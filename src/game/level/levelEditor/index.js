let size = 13;

let selectedTile = "empty";

const tiles = [
    "empty",
    "wall"
];

const onLoad = () => {
    let map = document.querySelector("#map");
    for (let y = 0; y < size; y++) {
        for (let x = 0; x < size; x++) {
            let node = document.createElement("div");
            node.classList.add("tile-empty");
            node.setAttribute("tile-name", "empty")
            node.setAttribute("x", x);
            node.setAttribute("y", y);

            node.onclick = () => {
                let tileName = node.getAttribute("tile-name");
                node.classList.remove(`tile-${tileName}`);
                node.classList.add(`tile-${selectedTile}`);
                node.setAttribute("tile-name", selectedTile);
            }

            map.appendChild(node);
        }
    }

    let tileSelect = document.querySelector("#tile-select")
    tiles.forEach((tileName) => {
        let container = document.createElement("div");
        container.classList.add("tile-select-container");

        let tile = document.createElement("div");
        tile.classList.add(`tile-${tileName}`);
        tile.classList.add("tile-select-item");
        if (selectedTile === tileName)
            tile.classList.add("tile-select-item-selected");

        tile.onclick = () => {
            selectedTile = tileName;
            document.querySelector(".tile-select-item-selected").classList.remove("tile-select-item-selected");
            tile.classList.add("tile-select-item-selected");
        }

        let text = document.createTextNode(tileName);

        container.appendChild(tile);
        container.appendChild(text);
        tileSelect.appendChild(container);
    });
}

document.addEventListener("DOMContentLoaded", function (event) {
    onLoad();
});

const generateMap = () => {
    const textarea = document.querySelector("#input");
    textarea.value = "";
    for (let x = 0; x < size; x++) {
        for (let y = 0; y < size; y++) {
            const tile = document.querySelector(`[x="${x}"][y="${y}"]`);
            textarea.value += `${tile.getAttribute("tile-name")} ${x} ${y}\n`;
        }
    }
}

const loadMap = () => {
    const textarea = document.querySelector("#input");

    textarea.value.split('\n').forEach(row => {
        const values = row.split(" ");

        const tile = document.querySelector(`[x="${values[1]}"][y="${values[2]}"]`);
        let tileName = tile.getAttribute("tile-name");
        tile.classList.remove(`tile-${tileName}`);
        tile.classList.add(`tile-${values[0]}`);
        tile.setAttribute("tile-name", values[0]);
    })
}