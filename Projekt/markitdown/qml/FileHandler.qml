import QtQuick
import Qt.labs.platform
import pb.pk.markitdown 1.0

Item {
    id: fileHandler
    enum ExportFormats {
        Html = 1,
        Pdf = 2
    }

    readonly property var formatData: ({
                                           "1": {
                                               "nameFilters": ["HTML document (*.html)"],
                                               "defaultSuffix": "html"
                                           },
                                           "2": {
                                               "nameFilters": ["PDF document (*.pdf)"],
                                               "defaultSuffix": "pdf"
                                           }
                                       })

    signal fileSavedAs(string filename)
    signal fileExportedTo(string filename, int exportFormat)

    function createNewFileOrOverwrite() {
        createFileDialog.createNewFileOrOverwrite()
    }

    function openFile() {
        openFileDialog.openFile()
    }

    function saveFileAs() {
        saveFileAsDialog.saveFileAs()
    }

    function exportToFile(exportFormat) {
        exportToFileDialog.exportToFile(exportFormat)
    }

    readonly property FileDialog createFileDialog: FileDialog {
        id: createFileDialog
        currentFile: ""
        folder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
        nameFilters: ["Markdown document (*.md)"]
        fileMode: FileDialog.SaveFile
        defaultSuffix: "md"
        acceptLabel: "Create"
        title: "File to create"
        onAccepted: () => {
                        MarkdownFileManager.save(createFileDialog.file, "")
                        TabManager.createTab(createFileDialog.file)
                        // create Tab etc.
                        createFileDialog.file = ""
                    }

        function createNewFileOrOverwrite() {
            if (!createFileDialog.visible) {
                createFileDialog.open()
            }
        }
    }

    readonly property FileDialog openFileDialog: FileDialog {
        id: openFileDialog
        currentFile: ""
        folder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
        nameFilters: ["Markdown document (*.md)"]
        fileMode: FileDialog.OpenFile
        defaultSuffix: "md"
        acceptLabel: "Open"
        title: "File to open"
        onAccepted: () => {
                        TabManager.createTab(openFileDialog.file)
                        // create Tab etc.
                        openFileDialog.file = ""
                    }

        function openFile() {
            if (!openFileDialog.visible) {
                openFileDialog.open()
            }
        }
    }

    readonly property FileDialog saveFileAsDialog: FileDialog {
        id: saveFileAsDialog
        currentFile: ""
        folder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
        nameFilters: ["Markdown document (*.md)"]
        fileMode: FileDialog.SaveFile
        defaultSuffix: "md"
        acceptLabel: "Save"
        title: "File to save"
        onAccepted: () => {
                        fileSavedAs(saveFileAsDialog.file)
                        saveFileAsDialog.file = ""
                    }

        function saveFileAs() {
            if (!saveFileAsDialog.visible) {
                saveFileAsDialog.open()
            }
        }
    }

    readonly property FileDialog exportToFileDialog: FileDialog {
        id: exportToFileDialog
        currentFile: ""
        folder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
        nameFilters: fileHandler.formatData[`${exportToFileDialog.exportFormat}`].nameFilters
        fileMode: FileDialog.SaveFile
        defaultSuffix: fileHandler.formatData[`${exportToFileDialog.exportFormat}`].defaultSuffix
        acceptLabel: "Export"
        title: "Export to file"
        onAccepted: () => {
                        fileExportedTo(exportToFileDialog.file, exportFormat)
                        exportToFileDialog.file = ""
                    }
        property int exportFormat: FileHandler.ExportFormats.Html

        function exportToFile(_exportFormat) {
            exportToFileDialog.exportFormat = _exportFormat
            if (!exportToFileDialog.visible) {
                exportToFileDialog.open()
            }
        }
    }
}
