param(
    [string]$DatasheetPath = "datasheet/lpc17xx_um_unlocked.pdf",
    [string]$WorkspaceRoot = ".",
    [int]$Dpi = 300
)

$ErrorActionPreference = "Stop"

$root = (Resolve-Path $WorkspaceRoot).Path
$datasheet = Join-Path $root $DatasheetPath
if (-not (Test-Path $datasheet)) {
    throw "No se encontró el datasheet en: $datasheet"
}

$tmpDir = Join-Path $root "tmp/datasheet_pipeline"
$pageDir = Join-Path $tmpDir "pages"
$cropDir = Join-Path $tmpDir "crops"
$outImgDir = Join-Path $root "documentacion latex/images"
$inventoryPath = Join-Path $root "documentacion latex/figure_inventory.csv"

New-Item -ItemType Directory -Force -Path $pageDir | Out-Null
New-Item -ItemType Directory -Force -Path $cropDir | Out-Null
New-Item -ItemType Directory -Force -Path $outImgDir | Out-Null

$figures = @(
    @{ section = "1.5 Diagrama de bloques"; page = 8;  x = 220; y = 360; w = 2140; h = 2600; output = "lpc1769_block_diagram.png"; source_label = "Fig 1. LPC1768 simplified block diagram" },
    @{ section = "1.6 Vista general de arquitectura"; page = 11; x = 220; y = 360; w = 2000; h = 2570; output = "lpc1769_ahb_matrix_detailed.png"; source_label = "Fig 2. LPC1768 block diagram, CPU and buses" },
    @{ section = "2.2 Mapa de memoria"; page = 13; x = 190; y = 120; w = 2920; h = 2320; output = "lpc17xx_system_memory_map.png"; source_label = "Fig 3. LPC17xx system memory map" },
    @{ section = "7.1 Configuración de pines LPC17xx"; page = 92; x = 610; y = 370; w = 1340; h = 980; output = "lpc17xx_pin_configuration_tfbga100.png"; source_label = "Fig 16. Pin configuration TFBGA100 package" }
)

Add-Type -AssemblyName System.Drawing

function Crop-Image {
    param(
        [string]$SourcePath,
        [string]$DestPath,
        [int]$X,
        [int]$Y,
        [int]$W,
        [int]$H
    )

    $img = [System.Drawing.Bitmap]::new($SourcePath)
    try {
        $rect = [System.Drawing.Rectangle]::new($X, $Y, $W, $H)
        $crop = $img.Clone($rect, $img.PixelFormat)
        try {
            $crop.Save($DestPath, [System.Drawing.Imaging.ImageFormat]::Png)
        }
        finally {
            $crop.Dispose()
        }
    }
    finally {
        $img.Dispose()
    }
}

$inventory = @()

foreach ($fig in $figures) {
    $prefix = Join-Path $pageDir ("page_{0}" -f $fig.page)
    & pdftoppm -png -r $Dpi -f $fig.page -l $fig.page $datasheet $prefix | Out-Null

    $pageImage = "{0}-{1:D3}.png" -f $prefix, $fig.page
    if (-not (Test-Path $pageImage)) {
        throw "No se generó la página renderizada esperada: $pageImage"
    }

    $cropImage = Join-Path $cropDir $fig.output
    Crop-Image -SourcePath $pageImage -DestPath $cropImage -X $fig.x -Y $fig.y -W $fig.w -H $fig.h

    $finalImage = Join-Path $outImgDir $fig.output
    Copy-Item $cropImage $finalImage -Force

    $inventory += [PSCustomObject]@{
        section = $fig.section
        datasheet_page = $fig.page
        source_figure = $fig.source_label
        dpi = $Dpi
        crop_x = $fig.x
        crop_y = $fig.y
        crop_w = $fig.w
        crop_h = $fig.h
        output_file = ("images/{0}" -f $fig.output)
    }
}

$inventory | Export-Csv -Path $inventoryPath -NoTypeInformation -Encoding UTF8
Write-Host "Pipeline completado. Inventario: $inventoryPath"
