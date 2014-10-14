/** The application's about window.*/
var aboutWindow = null;




/** @brief Create a window to show about window.
 *  @param appRoot The link to Application root element.
 *  @param parent The link to parent element.
 *  @return true if window is created and false if has some errors.
 *  @author Andrew Shapovalov*/
function createAboutWindow(appRoot, parent)
{
    var tmp = Qt.createComponent("../AboutWindow.qml");
    var options = { "id": "aboutWindow",
                    "parent": parent,
                    "rootApp" : appRoot};
    aboutWindow = tmp.createObject(parent, options);
    if(aboutWindow === null)
    {
        return false;
    }

    return true;
}
