import QtQuick
import Qt.labs.platform
import pb.pk.markitdown 1.0

Item {
    function createNewFileOrOverwrite() {
        createFileDialog.createNewFileOrOverwrite()
    }

    function openFile() {
        openFileDialog.openFile()
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
}
