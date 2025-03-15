
    // Load DOMContent 
document.addEventListener('DOMContentLoaded', function() {

    //Transform the JSON data into a JavaScript Object
    const paintings = JSON.parse(content);
    // Parse through content JSON

    //To locate the ids "details", "paintings ul" and "details figure"

    const details = document.querySelector("#details");
    const list = document.querySelector("#paintings ul");
    const figure = document.querySelector("#details figure")
    // select paintings unordered list and figures in details

    // Call the function generateThumbList to
    generateThumbList(list, paintings);

    // use event delegation to handle clicks in list
    // we want to click on the list so that we don't have to
    // keep adding event listeners to children
    list.addEventListener('click', function(e) {
        if (e.target && e.target.tagName == "IMG") {
            displayPaintingLarge(e.target);
        }
    })

    function generateThumbList(list, paintings) {
        //loop thru list of paintings and create <li><img></li>
        // create list elements, create file traversal string to the source
        // then append the image and list elements
        for (p of paintings) {
            const item = document.createElement('li');
            const thumb = document.createElement('img');
            thumb.src = "images/small/" + p.id + ".jpg";
            thumb.alt = p.title;
            thumb.dataset.id = p.id;
            item.appendChild(thumb);
            list.appendChild(item);
        }
    }


    function displayPaintingLarge(clickedThumbImage) {
        //retrieve the painting id from data-id attribute
        // use dataset that was previously initialized to find the painting
        let id = clickedThumbImage.dataset.id;
        
        //find that painting in the array

        const painting = paintings.find( function (p) { return p.id == id; } )

        //display the found painting
        // use textContent to add text from painting and querying painting attributes
        document.querySelector('#title').textContent = painting.title;
        document.querySelector('#artist').textContent = "By " + painting.artist;
        let image = document.createElement('img');
        image.src = "images/large/" + painting.id + ".jpg";
        // create source route for images

        //clear previous features

        figure.innerHTML = "";

        // display all features for this painting

        displayFeatures(painting.features);
        
        // add painting to image

        figure.appendChild(image);
    }

    function displayFeatures(features) {
        for (let f of features) {
            displaySingleFeatureRectangle(f);
        }
    }

    // do simple math for x and y of upperleft and lowerright to define the confines of the image box
    function displaySingleFeatureRectangle(feature) {
        let rect = document.createElement('div');
        rect.className = "box";
        rect.style.position = "absolute"
        rect.style.left = feature.upperLeft[0] + "px";
        rect.style.top = feature.upperLeft[1] + "px";
        rect.style.width = (feature.lowerRight[0] - feature.upperLeft[0]) + "px";
        rect.style.height = (feature.lowerRight[1] - feature.upperLeft[1]) + "px";

        // add event handlers for the feature rectangle
        // define textContent from feature's description when mouseover and mouseout
        rect.addEventListener('mouseover', function () {
            document.querySelector("#description").textContent = feature.description;
        });
        rect.addEventListener('mouseout', function () {
            document.querySelector("#description").textContent = "";
        });

        // add the feature rectangle to the <figure> parent
        figure.appendChild(rect);
    }




});